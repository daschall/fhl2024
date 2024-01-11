#include "btree.h"

namespace SE
{
	void BTree::InsertRow(Value val)
	{
		Page* page = Position(val, true);
		assert(page->IsLeafLevel());

		page->InsertRow(val);
	}

	Value BTree::Open()
	{
		Page* page = Position(0, false);

		return page->GetRow(0);
	}

	Page* BTree::Position(Value val, bool forInsert)
	{
		Page* page = GetGlobalBufferPool()->FindPage(m_rootPageID);

		if (page->IsLeafLevel())
		{
			Value firstVal = page->GetRow(0);
			Value lastVal = page->GetLastRow();
			
			assert(firstVal <= val && (forInsert || lastVal >= val));
		}
		else
		{
			// Traverse the tree
			//
		}

		return page;
	}

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

	BTreeSession::BTreeSession(BTree* btree)
	{
		m_btree = btree;
		m_lastKey = 0;
		m_firstRowReturned = false;
	}

	void BTreeSession::Open()
	{
		m_lastKey = m_btree->Open();
		m_firstRowReturned = false;
	}

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