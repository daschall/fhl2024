#include "page.h"
#include "common/value.h"
#include "interfaces/istorage.h"

namespace SE
{
	// This class implements a BTree structure. It is currently in-memory.
	// Each row contains one 'Value' which is also the key.
	//
	class BTree
	{
	public:
		BTree();

		// Implement accessors to get rows from the tree.
		//
		Value GetFirstRow();
		Value GetNextRow(Value val);

		// Insert rows into the tree.
		//
		void InsertRow(Value val);

	private:
		// Find the page into which a scan or insert needs to go.
		//
		Page* Position(Value val, bool forInsert);

		// Metadata about the BTree which help traverse the tree.
		//
		unsigned int m_rootPageID;
		unsigned int m_rootLevel;
	};

	// A session operates on an index and stores progress of a scan.
	//
	class BTreeSession: public IStorage
	{
	public:
		BTreeSession(BTree* btree);

		// Implement storage interfaces for an index.
		//
		void Open();
		bool GetRow(Value* val);
		void Close()
		{

		}
	private:

		// Store progress of the scan.
		//
		Value m_lastKey;
		bool m_firstRowReturned;
		BTree* m_btree;
	};
}