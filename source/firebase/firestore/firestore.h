#ifndef FIRESTORE_SRC_FIREBASE_FIRESTORE_FIRESTORE_H
#define FIRESTORE_SRC_FIREBASE_FIRESTORE_FIRESTORE_H

#include <grpcpp/grpcpp.h>
#include "google/firestore/v1/firestore.grpc.pb.h"

#ifdef FIRESTORE_VERBOSE
#include <iostream>
#define verbose std::cout
#else
class log_disabled_output : public std::ostream
{
public:
	log_disabled_output() :
		std::ostream(std::_Noinit, false)
	{
	}
};
static log_disabled_output log_disabled_output_instance;
#define verbose log_disabled_output_instance 
#endif

namespace firebase {
namespace firestore {

typedef google::protobuf::Map<std::string, google::firestore::v1::Value> DocumentFields;
typedef std::function<void(const google::firestore::v1::Document*)> ListenCallback;
typedef google::firestore::v1::Document Document;
typedef google::firestore::v1::Value Value;

/**
 * This file features a lightweight class that may be used to 
 * communicate with a Firestore database.
 *
 * The class uses the Firestore RPC protocols for communication.
 * Firestore RPC protocol documentation is found here:
 * https://firebase.google.com/docs/firestore/reference/rpc#google.firestore.v1.firestore
 *
 * This class has only been tested on Windows.
 *
 * To setup the authentication on Windows, you need to set the
 * following environment variables:
 * 1) GOOGLE_APPLICATION_CREDENTIALS=[PATH_TO_CREDENTIALS]
 *    See https://cloud.google.com/docs/authentication/getting-started
 *    for more information
 * 2) GRPC_DEFAULT_SSL_ROOTS_FILE_PATH=[SOLUTION_DIR]\grpc\etc\roots.pem
 */

class FIRESTORE_EXPORT Firestore
{
public:
	/**
	 * Initializes a channel to communicate with a Firestore database
	 *
	 * \param project_id   Project ID of the Firestore database, find it on https://console.cloud.google.com
	 * \param database_id  Should be set to "(default)", see https://stackoverflow.com/questions/48584648/how-to-find-the-database-id-of-a-cloud-firestore-project
	 */
	Firestore(const std::string &project_id, const std::string &database_id);
	~Firestore();

	/**
	 * Retrieves the document at path 'document_path' from the current Firestore database.
	 *
	 * \param document_path The path of the document to update or insert
	 * \param document_out  Output document object
	 * \returns             True on successful document retrieval
	 */
	bool GetDocument(const std::string &document_path, Document *document_out);

	/**
	 * Updates or inserts a new document at path 'document_path' in the current Firestore database.
	 *
	 * \param document_path The path of the document to update or insert
	 * \param new_document  Document to update or insert
	 * \param document_out  Updated document object, as received from the database (optional)
	 * \returns             True on successful document update
	 */
	bool UpdateDocument(const std::string &document_path, const Document &new_document, Document *document_out=nullptr);

	/**
	 * Start listening to changes in document at path 'document_path' in the current Firestore database.
	 * Whenever a change is detected, the callback function provided will be called with
	 * the updated document as its only argument.
	 *
	 * Note: The callback function will be automatically invoked one time 
	 *       once the Listen call has finished setting up.
	 *
	 * Note: When a document is removed, or the requested document does not exists,
	 *       the callback function will be called with document=nullptr.
	 *
	 * \param document_path The path of the document to update or insert
	 * \param new_document  Document to update or insert
	 * \returns             The ID for the newly created listener thread.
	 *                      This value will be negative on error.
	 */
	int32_t Listen(const std::string &document_path, const ListenCallback &callback);

	/**
	 * Stop listening to changes in document at path 'document_path' in the current Firestore database.
	 * Call this function with the ID of the listener thread; returned by Listen.
	 *
	 * \param listen_id The ID of the listener thread; returned by Listen
	 */
	bool Unlisten(const int32_t listen_id);

	/**
	 * Returns a full document path:
	 * projects/{project_id}/databases/{database_id}/documents/{document_path}
	 */
	std::string GetFullDocumentPath(const std::string &document_path) const;

private:
	const std::string project_id;
	const std::string database_id;
	const std::string database_base_path;

	std::unique_ptr<google::firestore::v1::Firestore::Stub> stub;
	std::shared_ptr<grpc::ChannelCredentials> credentials;
	std::shared_ptr<grpc::Channel> channel;

	class ListenerThread
	{
		friend class Firestore;
	public:
		ListenerThread(const Firestore &firestore,
					   const std::string &document_path,
					   const ListenCallback &callback);

		void StartListening();
		void StopListening();
		bool IsListening() const;
		const void *const GetTag() const;
		std::string GetDocumentPath() const;

	private:
		void ListenInternal() const;

		static int32_t current_listener_thread_tag;
		void *const tag;

		const Firestore &firestore;
		const std::string document_path;
		const ListenCallback callback;

		std::thread thread;

		std::atomic<bool> listening;
	};
	friend class ListenerThread;

	std::map<int32_t, std::shared_ptr<ListenerThread>> listener_threads;
};

} // namespace firestore
} // namespace firebase

#endif // FIRESTORE_SRC_FIREBASE_FIRESTORE_FIRESTORE_H
