#include "page.h"
#include "buffer.h"
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

		// Check if a page's level is the root level of this tree.
		//
		bool IsRootLevel(unsigned int level)
		{
			return (level == m_rootLevel);
		}

		// Implement accessors to get rows from the tree.
		//
		Page* GetFirstLeafPage();
		Value GetRow(PageId* pageId, unsigned int* slot);

		// Insert rows into the tree.
		//
		void InsertRow(Value val);

		void Split(Value val);

		Value TransferRows(Page* leftPage, Page* rightPage);

		Page* FindChildPage(Page* page, Value val);

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
		PageId m_currentPageId;
		unsigned int m_currentSlot;
		BTree* m_btree;
	};
}