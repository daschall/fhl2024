#include "btree.h"

namespace SE
{
	BTree::BTree()
	{
		m_rootLevel = 0;
		m_rootPageID = GetGlobalBufferPool()->GetNewPage(m_rootLevel)->GetPageId();
	}

	// Insert single row
	//
	void BTree::InsertRow(Value val)
	{
		Page* page = Position(val, true);
		assert(page->IsLeafLevel());

		page->InsertRow(val);
	}

	// Get the first key of the BTree.
	//
	Value BTree::GetFirstRow()
	{
		Page* page = Position(0, false);

		return page->GetRow(0);
	}

	// Traverse the tree to find the leaf page either for read or write.
	//
	Page* BTree::Position(Value val, bool forInsert)
	{
		Page* page = GetGlobalBufferPool()->FindPage(m_rootPageID);

		if (page->IsLeafLevel())
		{
			if (!forInsert)
			{
				Value firstVal = page->GetRow(0);
				Value lastVal = page->GetLastRow();

				assert(firstVal <= val && lastVal >= val);
			}
		}
		else
		{
			// Traverse the tree. Yet to be implemented.
			//
		}

		return page;
	}

	// Get the next key of the tree given a key.
	// -1 is used to indicate end of scan.
	//
	Value BTree::GetNextRow(Value val)
	{
		Page* page = Position(val, false);
		assert(page->IsLeafLevel());

		for (unsigned int slot = 0; slot < page->GetSlotCount(); slot++)
		{
			Value slotVal = page->GetRow(slot);
			if (slotVal <= val)
			{
				continue;
			}

			return slotVal;
		}

		return -1;
	}

	// Initialize a session with the BTree.
	//
	BTreeSession::BTreeSession(BTree* btree)
	{
		m_btree = btree;
		m_lastKey = 0;
		m_firstRowReturned = false;
	}

	// Open the session and collect the first key.
	//
	void BTreeSession::Open()
	{
		m_lastKey = m_btree->GetFirstRow();
		m_firstRowReturned = false;
	}

	// Get the next row of the tree in the session.
	//
	bool BTreeSession::GetRow(Value* rgvals)
	{
		Value nextVal = -1;

		if (!m_firstRowReturned)
		{
			nextVal = m_lastKey;
			m_firstRowReturned = true;
		}
		else
		{
			nextVal = m_btree->GetNextRow(m_lastKey);
			m_lastKey = nextVal;
		}

		if (nextVal == -1)
		{
			return false;
		}

		rgvals[0] = nextVal;
		return true;
	}
}