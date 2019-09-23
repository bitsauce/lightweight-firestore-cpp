#include <iostream>

#include "firebase/firestore/firestore.h"

using firebase::firestore::Firestore;
using firebase::firestore::Transaction;
using firebase::firestore::Document;
using firebase::firestore::Value;
using firebase::firestore::DocumentFields;

std::string getRandomAZString(const int size)
{
	std::string str = "";
	for(size_t i = 0; i < size; i++)
	{
		str += 'a' + rand() % ('z' - 'a');
	}
	return str;
}

void waitUntil(const std::atomic<bool>& b)
{
	while(!b) { std::this_thread::sleep_for(std::chrono::milliseconds(100)); }
}

int main()
{
	std::string project_id = "firestore-test-240401";
	std::string database_id = "(default)";

	Firestore *firestore = new Firestore(project_id, database_id);

	// Start tests
	const std::string collection = "firestore_test";

	// Testing: GetDocument() with document_out=nullptr
	{
		assert(firestore->GetDocument(collection + "/document", nullptr) == false);
	}

	// Testing: GetDocument() when document at document_path is missing
	{
		Document document;
		assert(firestore->GetDocument(collection + "/null", &document) == false);
	}

	// Testing:
	// Creating document with UpdateDocument() and reading
	// the document back with GetDocument()
	{
		const std::string document_path = collection + "/user";

		const int         random_age  = rand();
		const std::string random_name = getRandomAZString(6);
		
		// Insert new document with UpdateDocument
		{
			Document document_out;

			// Create document
			Document new_document;
			DocumentFields& fields = *new_document.mutable_fields();
			{
				Value v;
				v.set_integer_value(random_age);
				fields["Age"] = v;
			}
			{
				Value v;
				v.set_string_value(random_name);
				fields["Name"] = v;
			}

			// Update document
			assert(firestore->UpdateDocument(document_path, new_document, &document_out) == true);

			// Verify that document_out contains the random values
			{
				DocumentFields fields = document_out.fields();
				DocumentFields::iterator itr;
				itr = fields.find("Name");
				assert(itr != fields.end());
				assert(itr->second.string_value() == random_name);
				itr = fields.find("Age");
				assert(itr != fields.end());
				assert(itr->second.integer_value() == random_age);
			}
		}

		// Read document with GetDocument() and verity values
		{
			Document document;
			assert(firestore->GetDocument(document_path, &document) == true);
			DocumentFields fields = document.fields();
			DocumentFields::iterator itr;
			itr = fields.find("Name");
			assert(itr != fields.end());
			assert(itr->second.string_value() == random_name);
			itr = fields.find("Age");
			assert(itr != fields.end());
			assert(itr->second.integer_value() == random_age);
		}
	}

	// Testing: UpdateDocument() when document_out=nullptr
	{
		const std::string document_path = collection + "/update_document_test_0";

		const int random_value = rand();

		// Insert new document with UpdateDocument
		{
			Document new_document;
			DocumentFields& fields = *new_document.mutable_fields();
			Value v;
			v.set_integer_value(random_value);
			fields["Random Value"] = v;
			assert(firestore->UpdateDocument(document_path, new_document) == true);
		}

		// Use GetDocument to verify that document exists and that
		// field "Random Value" has the right value
		{
			Document document;
			assert(firestore->GetDocument(document_path, &document) == true);
			DocumentFields fields = document.fields();
			DocumentFields::iterator itr;
			itr = fields.find("Random Value");
			assert(itr != fields.end());
			assert(itr->second.integer_value() == random_value);
		}
	}

	// Testing: Listen() when callback is invalid
	{
		assert(firestore->Listen("null/null", nullptr) < 0);
	}

	// Testing: Listen() when document does not exists
	{
		std::atomic<bool> listen_initialized = false;
		int32_t listen_id = firestore->Listen("null/null", [&](const Document *document) {
			assert(document == nullptr);
			listen_initialized = true;
		});
		assert(listen_id >= 0);

		// Wait until listen finished setting up
		waitUntil(listen_initialized);

		// Test Unlisten call
		assert(firestore->Unlisten(listen_id) == true);
	}

	// Testing: Listen() when a document value is changed
	{
		const std::string document_path = collection + "/listen_test_0";

		const int initial_value = rand();
		const int changed_value = initial_value + 123456;

		// Create document with value = initial_value
		{
			Document new_document;
			DocumentFields& fields = *new_document.mutable_fields();
			Value v;
			v.set_integer_value(initial_value);
			fields["Value"] = v;
			assert(firestore->UpdateDocument(document_path, new_document) == true);
		}

		std::atomic<bool> listen_initialized = false;
		std::atomic<bool> random_value_verified = false;
		int32_t listen_id = firestore->Listen(document_path, [&](const Document *document)
		{
			// Will be false the first time
			if(listen_initialized)
			{
				// Verify that value == changed_value
				DocumentFields fields = document->fields();
				DocumentFields::iterator itr;
				itr = fields.find("Value");
				assert(itr != fields.end());
				assert(itr->second.integer_value() == changed_value);
				random_value_verified = true;
			}
			listen_initialized = true;
		});
		assert(listen_id >= 0);

		// Wait until listen finished setting up
		waitUntil(listen_initialized);

		// Make a change with UpdateDocument
		{
			Document new_document;
			DocumentFields& fields = *new_document.mutable_fields();
			Value v;
			v.set_integer_value(changed_value);
			fields["Value"] = v;
			assert(firestore->UpdateDocument(document_path, new_document) == true);
		}

		// Wait until random value was registered and verified by the listener thread
		waitUntil(random_value_verified);

		// Test Unlisten call
		assert(firestore->Unlisten(listen_id) == true);
	}

	// Testing: Unlisten() when listening thread does not exists
	{
		assert(firestore->Unlisten(-1) == false);
	}

	// Testing: Updating document via a transaction
	{
		const std::string document_path = collection + "/transaction_test_0";

		const int random_value = rand();

		// Setup document with random value
		{
			Document new_document;
			DocumentFields& fields = *new_document.mutable_fields();
			Value v;
			v.set_integer_value(random_value);
			fields["Random Value"] = v;

			// Update document via a transaction
			std::shared_ptr<Transaction> transaction = firestore->BeginTransaction();
			assert(transaction != nullptr);
			assert(transaction->UpdateDocument(document_path, new_document) == true);
			assert(firestore->CommitTransaction(transaction) == true);
		}

		// Verify that the random value was written
		{
			Document document_out;
			firestore->GetDocument(document_path, &document_out);
			DocumentFields fields = document_out.fields();
			DocumentFields::iterator itr;
			itr = fields.find("Random Value");
			assert(itr != fields.end());
			assert(itr->second.integer_value() == random_value);
		}
	}

	// Test commented out as it is a bit inconsistent
	//// Testing: Updating a document that is in use by a transaction (should time-out)
	//{
	//	const std::string document_path = collection + "/transaction_test_1";

	//	const int64_t random_value = rand();

	//	// Setup document with random value
	//	{
	//		Document new_document;
	//		DocumentFields& fields = *new_document.mutable_fields();
	//		Value v;
	//		v.set_integer_value(random_value);
	//		fields["Value"] = v;
	//		assert(firestore->UpdateDocument(document_path, new_document) == true);
	//	}

	//	// Setup transaction
	//	std::shared_ptr<Transaction> transaction;
	//	{
	//		// Get document through the transaction
	//		Document document_out;
	//		transaction = firestore->BeginTransaction();
	//		assert(transaction != nullptr);
	//		assert(transaction->GetDocument(document_path, &document_out) == true);

	//		// Update a value in the document
	//		DocumentFields& fields = *document_out.mutable_fields();
	//		Value v;
	//		v.set_integer_value(fields["Value"].integer_value() + 1); // Write value + 1
	//		fields["Value"] = v;
	//		assert(transaction->UpdateDocument(document_path, document_out) == true);
	//	}

	//	// Change the document after the transaction was started, but before it was committed
	//	{
	//		Document new_document;
	//		DocumentFields& fields = *new_document.mutable_fields();
	//		Value v;
	//		v.set_integer_value(random_value + 2); // Write value + 2
	//		fields["Value"] = v;
	//		assert(firestore->UpdateDocument(document_path, new_document) == false); // Timeout
	//	}

	//	// Commit transaction
	//	{
	//		assert(firestore->CommitTransaction(transaction) == false); // Expired
	//	}

	//	// Verify value
	//	{
	//		Document document_out;
	//		firestore->GetDocument(document_path, &document_out);
	//		DocumentFields fields = document_out.fields();
	//		DocumentFields::iterator itr;
	//		itr = fields.find("Value");
	//		assert(itr != fields.end());
	//		assert(itr->second.integer_value() == random_value);
	//	}
	//}

	// Verify that destructor works as expected
	// (may take a minute for the listerner threads to finish
	//  as they may be waiting for a NO_CHANGE signal)
	delete firestore;

	std::cout << "All tests passed successfully" << std::endl;

	return 0;
}
