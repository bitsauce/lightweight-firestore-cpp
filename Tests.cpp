#include <iostream>

#include "firebase/firestore/firestore.h"

using firebase::firestore::Firestore;
using firebase::firestore::Document;
using firebase::firestore::Value;
using firebase::firestore::DocumentFields;

void main()
{
	std::string project_id = "firestore-test-240401";
	std::string database_id = "(default)";

	Firestore *firestore = new Firestore(project_id, database_id);

	// Testing: GetDocument() with document_out=nullptr
	{
		assert(firestore->GetDocument("users/document", nullptr) == false);
	}

	// Testing: GetDocument() when document at document_path is missing
	{
		Document document;
		assert(firestore->GetDocument("null/null", &document) == false);
	}

	// Testing: GetDocument() when document at document_path exists
	// Expects a database where document "users/john_doe" already exists,
	// with the following fields:
	// { "Name": "John Doe", "Age": 23 }
	{
		Document document;
		assert(firestore->GetDocument("users/john_doe", &document) == true);
		DocumentFields fields = document.fields();
		DocumentFields::iterator itr;
		itr = fields.find("Name");
		assert(itr != fields.end());
		assert(itr->second.string_value() == "John Doe");
		itr = fields.find("Age");
		assert(itr != fields.end());
		assert(itr->second.integer_value() == 23);
	}

	// Testing: UpdateDocument() with document_out=nullptr
	{
		const int random_value = rand();

		// Insert new document with UpdateDocument
		{
			Document new_document;
			DocumentFields &fields = *new_document.mutable_fields();
			Value v;
			v.set_integer_value(random_value);
			fields["Random Value"] = v;
			assert(firestore->UpdateDocument("users/new_user", new_document) == true);
		}

		// Use GetDocument to verify that document exists and that
		// field "Random Value" has the right value
		{
			Document document;
			assert(firestore->GetDocument("users/new_user", &document) == true);
			DocumentFields fields = document.fields();
			DocumentFields::iterator itr;
			itr = fields.find("Random Value");
			assert(itr != fields.end());
			assert(itr->second.integer_value() == random_value);
		}
	}


	// Testing: UpdateDocument() with document_out != nullptr
	{
		const int random_value = rand();
		Document document;

		// Insert new document with UpdateDocument
		{
			Document new_document;
			DocumentFields &fields = *new_document.mutable_fields();
			Value v;
			v.set_integer_value(random_value);
			fields["Random Value"] = v;
			assert(firestore->UpdateDocument("users/new_user", new_document, &document) == true);
		}

		// Verify that document_out contains the random value
		{
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
		while(!listen_initialized);

		// Test Unlisten call
		assert(firestore->Unlisten(listen_id) == true);
	}

	// Testing: Listen() when a document value is changed
	{
		const int random_value = rand();
		std::atomic<bool> listen_initialized = false;
		std::atomic<bool> random_value_verified = false;
		int32_t listen_id = firestore->Listen("users/new_user", [&](const Document *document) {
			// Will be false the first time
			if(listen_initialized)
			{
				// Verify that document contains the random value
				DocumentFields fields = document->fields();
				DocumentFields::iterator itr;
				itr = fields.find("Random Value");
				assert(itr != fields.end());
				assert(itr->second.integer_value() == random_value);
				random_value_verified = true;
			}
			listen_initialized = true;
		});
		assert(listen_id >= 0);

		// Wait until listen finished setting up
		while(!listen_initialized);

		// Make a change with UpdateDocument
		Document new_document;
		DocumentFields &fields = *new_document.mutable_fields();
		Value v;
		v.set_integer_value(random_value);
		fields["Random Value"] = v;
		assert(firestore->UpdateDocument("users/new_user", new_document) == true);

		// Wait until random value was verified
		while(!random_value_verified);

		// Test Unlisten call
		assert(firestore->Unlisten(listen_id) == true);
	}

	// Testing: Unlisten() when listening thread does not exists
	{
		assert(firestore->Unlisten(-1) == false);
	}

	// Verify that destructor works as expected
	// (may take a minute for the listerner threads to finish
	//  as they may be waiting for a NO_CHANGE signal)
	delete firestore;

	std::cout << "All tests were passed successfully" << std::endl;
}
