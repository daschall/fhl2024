#include "interfaces/btreesession.h"
#include "interfaces/btree.h"

#include "page.h"

namespace SE
{
	// Initialize a session with the BTree.
	//
	BTreeSession::BTreeSession(BTree* btree)
	{
		m_btree = btree;
		m_currentPageId = 0;
		m_currentSlot = 0;
	}

	// Open the session and collect the first key.
	//
	void BTreeSession::Open()
	{
		m_currentPageId = m_btree->GetFirstLeafPage()->GetPageId();
		m_currentSlot = 0;
	}

	// Get the next row of the tree in the session.
	//
	bool BTreeSession::GetRow(Value* rgvals)
	{
		Value nextVal = m_btree->GetRow(&m_currentPageId, &m_currentSlot);

		if (nextVal == -1)
		{
			return false;
		}

		rgvals[0] = nextVal;
		return true;
	}
}