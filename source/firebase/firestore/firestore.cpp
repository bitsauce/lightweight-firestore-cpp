#include "firestore.h"

namespace firebase {
namespace firestore {

Firestore::Firestore(const std::string &project_id, const std::string &database_id) :
	project_id(project_id),
	database_id(database_id),
	database_base_path("projects/" + project_id + "/databases/" + database_id)
{
	credentials = grpc::GoogleDefaultCredentials();
	channel = grpc::CreateChannel("firestore.googleapis.com:443", credentials);
	stub = google::firestore::v1::Firestore::NewStub(channel);
}

Firestore::~Firestore()
{
	// Clean up listener threads
	for(auto itr : listener_threads)
	{
		itr.second->StopListening();
		auto &t = itr.second->thread;
		if(t.joinable())
		{
			t.join();
		}
	}
	listener_threads.clear();
}

bool Firestore::GetDocument(const std::string &document_path, Document *document_out)
{
	// Make sure we were provided a document object to write to
	if(document_out == nullptr)
	{
		std::cerr << "Firestore::GetDocument(): No output document provided (document_out=nullptr)" << std::endl;
		return false;
	}

	// Create a document request
	// We will the request document with path:
	// projects/{project_id}/databases/{database_id}/documents/{document_path}
	google::firestore::v1::GetDocumentRequest request;
	request.set_name(GetFullDocumentPath(document_path));

	grpc::ClientContext client_context;
	grpc::Status s = stub->GetDocument(&client_context, request, document_out);
	if(!s.ok())
	{
		std::cout << "Firestore::GetDocument(): Received ok=false" << std::endl;
		std::cout << "Message:" << std::endl;
		std::cout << s.error_message() << std::endl;
		std::cout << s.error_details() << std::endl;
		return false;
	}
	return true;
}

bool Firestore::UpdateDocument(const std::string &document_path, const Document &new_document, Document *document_out)
{
	// If no output document, use a temp document
	Document temp;
	if(document_out == nullptr)
	{
		document_out = &temp;
	}

	// Make copy of new document
	Document *allocated_document = new Document(new_document);
	allocated_document->set_name(GetFullDocumentPath(document_path));

	// Create an update document request
	// We will the request to update document with path:
	// projects/{project_id}/databases/{database_id}/documents/{document_path}
	google::firestore::v1::UpdateDocumentRequest request;
	request.set_allocated_document(allocated_document); // UpdateDocumentRequest will handle deallocation

	grpc::ClientContext client_context;
	grpc::Status s = stub->UpdateDocument(&client_context, request, document_out);
	if(!s.ok())
	{
		std::cout << "Firestore::UpdateDocument(): Received ok=false" << std::endl;
		std::cout << "Message:" << std::endl;
		std::cout << s.error_message() << std::endl;
		std::cout << s.error_details() << std::endl;
		return false;
	}
	return true;
}

int32_t Firestore::Listen(const std::string &document_path, const ListenCallback &callback)
{
	verbose << "Firestore::Listen(): Listening for changes in document with path \"" << document_path << "\"" << std::endl;
	if(!callback)
	{
		std::cerr << "Firestore::Listen(): No callback function provided to listen call; skipping." << std::endl;
		return -1;
	}

	// Create a listener thread
	std::shared_ptr<ListenerThread> listener_thread(new ListenerThread(*this, document_path, callback));
	listener_thread->StartListening();

	// Map listener thread id to listener thread
	const int32_t listener_thead_id = (int32_t)listener_thread->GetTag();
	listener_threads[listener_thead_id] = listener_thread;
	return listener_thead_id;
}

bool Firestore::Unlisten(const int32_t listen_id)
{
	auto itr = listener_threads.find(listen_id);
	if(itr != listener_threads.end())
	{
		verbose << "Firestore::Listen(): Unlistening for changes in document with path \"" << itr->second->GetDocumentPath() << "\"" << std::endl;
		itr->second->StopListening();
		// TODO: Consider removing inactive ListenerThreads (however, this solution has issues if unlisten called from a listen thread)
		//listener_threads.erase(itr);
		return true;
	}
	else
	{
		std::cout << "Firestore::Unlisten(): Could not find listener thread with id=" << listen_id << std::endl;
		return false;
	}
}

std::string Firestore::GetFullDocumentPath(const std::string &document_path) const
{
	return database_base_path + "/documents/" + document_path;
}

int32_t Firestore::ListenerThread::current_listener_thread_tag = 0;

Firestore::ListenerThread::ListenerThread(const Firestore &firestore,
									  const std::string &document_path,
									  const ListenCallback &callback) :
	firestore(firestore),
	tag((void*)++current_listener_thread_tag), // Get a unique tag for this bi-directional stream
	document_path(document_path),
	callback(callback),
	listening(false)
{
}

void Firestore::ListenerThread::StartListening()
{
	listening = true;
	thread = std::thread(&Firestore::ListenerThread::ListenInternal, this);
}

void Firestore::ListenerThread::StopListening()
{
	listening = false;
}

std::string Firestore::ListenerThread::GetDocumentPath() const
{
	return document_path;
}

bool Firestore::ListenerThread::IsListening() const
{
	return listening;
}

const void *const Firestore::ListenerThread::GetTag() const
{
	return tag;
}

void Firestore::ListenerThread::ListenInternal() const
{
	std::shared_ptr<google::firestore::v1::ListenResponse> reply(new google::firestore::v1::ListenResponse);

	// To initiate a listen request, we have to specify a
	// set of target document(s) to listen to
	google::firestore::v1::Target::DocumentsTarget *documents_target = new google::firestore::v1::Target::DocumentsTarget;

	// We will listen to the document with path:
	// projects/{project_id}/databases/{database_id}/documents/{document_path}
	documents_target->add_documents(firestore.GetFullDocumentPath(document_path));

	// Create a target and attach the document target
	google::firestore::v1::Target *target = new google::firestore::v1::Target;
	target->set_allocated_documents(documents_target); // Target will handle deallocation
	target->set_once(false);                           // Keep listening after the initial document is received

	// Setup listen request
	google::firestore::v1::ListenRequest request;
	request.set_database(firestore.database_base_path);
	request.set_allocated_add_target(target); // ListenRequest will handle deallocation

	// Create a grpc client context
	grpc::ClientContext client_context;

	// Need to include google-cloud-resource-prefix in the header,
	// otherwise it won't connect
	client_context.AddMetadata("google-cloud-resource-prefix", firestore.database_base_path);

	// Initiate firestore listen call
	grpc::CompletionQueue cq; // Async queue
	std::unique_ptr<grpc::ClientAsyncReaderWriter<google::firestore::v1::ListenRequest, google::firestore::v1::ListenResponse>> rpc(
		firestore.stub->AsyncListen(&client_context, &cq, tag)
	);

	// Verify that stream initialization was successful
	void *recv_tag; bool ok;
	if(!cq.Next(&recv_tag, &ok))
	{
		std::cout << "Firestore::Listen(): Queue was shut down. Timeout? (Last call: StartCall)" << std::endl;
		return;
	}
	if(!ok || recv_tag != tag)
	{
		std::cout <<
			"Firestore::Listen(): Failed to initialize stream. " <<
			"cq.Next returned tag=" << recv_tag << " " <<
			"(expected tag=" << tag << ") " <<
			"and ok=" << ok << std::endl;
		return;
	}

	// Write the listen request
	// This will make the server listen for changes
	// in the documents that were added to the target
	rpc->Write(request, tag);
	if(!cq.Next(&recv_tag, &ok))
	{
		std::cout << "Firestore::Listen(): Queue was shut down. Timeout? (Last call: Write)" << std::endl;
		return;
	}
	if(!ok || recv_tag != tag)
	{
		std::cout <<
			"Firestore::Listen(): Failed to write to stream. " <<
			"cq.Next returned tag=" << recv_tag << " " <<
			"(expected tag=" << tag << ") " <<
			"and ok=" << ok << std::endl;
		return;
	}

	// Listening loop
	std::list<uint32_t> active_target_ids;
	do
	{
		// Get server response
		rpc->Read(reply.get(), tag);
		if(!cq.Next(&recv_tag, &ok)) // May block until next message is received
		{
			std::cout << "Firestore::Listen(): Queue was shut down. Timeout? (Last call: Read)" << std::endl;
			return;
		}
		if(!ok || recv_tag != tag)
		{
			std::cout <<
				"Firestore::Listen(): Failed to initialize stream. " <<
				"cq.Next returned tag=" << recv_tag << " " <<
				"(expected tag=" << tag << ") " <<
				"and ok=" << ok << std::endl;
			return;
		}

		// Process response
		const google::firestore::v1::ListenResponse::ResponseTypeCase response_type_case = reply->response_type_case();
		switch(response_type_case)
		{
			// ResponseTypeCase::kTargetChange:
			// This response is received whenever a change
			// occured in a server-side target
			case google::firestore::v1::ListenResponse::kTargetChange:
			{
				const google::firestore::v1::TargetChange &change = reply->target_change();

				// Check for error in target change
				const google::rpc::Status &cause = change.cause();
				int32_t code = cause.code();
				if(code != 0)
				{
					std::cout << "Firestore::Listen(): Received a non-zero rpc status code (code=" << code << ") " <<
						"with a ResponseTypeCase::kTargetChange response" << std::endl;
					std::cout << "Message:" << std::endl;
					std::cout << cause.message() << std::endl;
					return;
				}

				// Process target change reply
				const google::firestore::v1::TargetChange::TargetChangeType target_change_type = change.target_change_type();
				switch(target_change_type)
				{
					// TargetChangeType::NO_CHANGE:
					// This response is received periodically from the server
					// There are no associated target ids sent
					case google::firestore::v1::TargetChange::NO_CHANGE:
						verbose << "Firestore::Listen(): Received a target change response of type NO_CHANGE" << std::endl;
						break;

					// TargetChangeType::ADD:
					// This response is received once the server has added target(s)
					// Note:
					// - "For target_change_type=ADD, the order of the target IDs matches the order of the requests to add the targets.
					//    This allows clients to unambiguously associate server-assigned target IDs with added targets."
					// - Target IDs are unique for each ListenRequest.
					// TODO: Should add checks to remember all currently valid targets
					case google::firestore::v1::TargetChange::ADD:
						verbose << "Firestore::Listen(): Received a target change response of type ADD" << std::endl;
						for(int32_t id : change.target_ids())
						{
							active_target_ids.push_back(id);
							verbose << "Firestore::Listen(): Target with id=" << id << " added server-side" << std::endl;
						}
						break;

					// TargetChangeType::REMOVE:
					// This response is received once the server has removed target(s)
					case google::firestore::v1::TargetChange::REMOVE:
						verbose << "Firestore::Listen(): Received a target change response of type REMOVE" << std::endl;
						for(int32_t id : change.target_ids())
						{
							active_target_ids.remove(id);
							verbose << "Firestore::Listen(): Target with id=" << id << " removed server-side" << std::endl;
						}
						break;

					// TargetChangeType::REMOVE:
					// This response is received once the server has removed target(s)
					case google::firestore::v1::TargetChange::CURRENT:
						verbose << "Firestore::Listen(): Received a target change response of type CURRENT" << std::endl;
						for(int32_t id : change.target_ids())
						{
							verbose << "Firestore::Listen(): Target with id=" << id << " is now current" << std::endl;
						}
						break;

					// TargetChangeType::RESET:
					// This response is received once the server has reset target(s)
					case google::firestore::v1::TargetChange::RESET:
						verbose << "Firestore::Listen(): Received a target change response of type RESET" << std::endl;
						for(int32_t id : change.target_ids())
						{
							verbose << "Firestore::Listen(): Target with id=" << id << " reset" << std::endl;
						}
						break;

					default:
						std::cerr << "Firestore::Listen(): Received an nvalid TargetChangeType of value=" << target_change_type << std::endl;
						return;
				}
			}
			break;

			// ResponseTypeCase::kDocumentChange:
			// This response is received whenever a document change
			// occured in any listened documents on the server-side
			case google::firestore::v1::ListenResponse::kDocumentChange:
			{
				verbose << "Firestore::Listen(): Received document change response" << std::endl;
				const google::firestore::v1::DocumentChange &change = reply->document_change();
				for(int32_t id : change.target_ids()) // List of all target ids that map to this document
				{
					verbose << "Firestore::Listen(): Document target with id=" << id << " changed" << std::endl;
				}

				assert(callback);
				callback(&change.document());
			}
			break;

			// ResponseTypeCase::kDocumentDelete:
			// This response is received whenever a target document
			// was deleted on the server-side
			case google::firestore::v1::ListenResponse::kDocumentDelete:
			{
				verbose << "Firestore::Listen(): Received document deleted response" << std::endl;
				const google::firestore::v1::DocumentDelete &change = reply->document_delete();
				for(int32_t id : change.removed_target_ids()) // List of all target ids that map to this document
				{
					verbose << "Firestore::Listen(): Document target with id=" << id << " was removed or does not exists" << std::endl;
				}
				verbose << "Firestore::Listen(): Document \"" << change.document() << "\"" << std::endl;

				assert(callback);
				callback(nullptr);
			}
			break;

			// ResponseTypeCase::kDocumentRemove:
			// This response is received whenever a target document
			// was removed on the server-side
			// (unclear how it is different from kDocumentDelete)
			case google::firestore::v1::ListenResponse::kDocumentRemove:
			{
				verbose << "Firestore::Listen(): Received document deleted response" << std::endl;
				const google::firestore::v1::DocumentRemove &change = reply->document_remove();
				for(int32_t id : change.removed_target_ids()) // List of all target ids that map to this document
				{
					verbose << "Firestore::Listen(): Document target with id=" << id << " was removed or does not exists" << std::endl;
				}
				verbose << "Firestore::Listen(): Document \"" << change.document() << "\"" << std::endl;

				assert(callback);
				callback(nullptr);
			}
			break;

			case google::firestore::v1::ListenResponse::kFilter:
			default:
				std::cerr << "Firestore::Listen(): ResponseTypeCase " << response_type_case << " not implemented." << std::endl;
				break;
		}
	} while(listening);

	grpc::Status s;
	rpc->Finish(&s, tag);
	if(!s.ok())
	{
		std::cout << "Firestore::Listen(): Received ok=false on finish" << std::endl;
		std::cout << "Message:" << std::endl;
		std::cout << s.error_message() << std::endl;
		std::cout << s.error_details() << std::endl;
	}
}

} // namespace firestore
} // namespace firebase
