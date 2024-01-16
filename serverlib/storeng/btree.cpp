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

		if (page->IsFull())
		{
			Split(val);

			// Find new insert point after split.
			//
			page = Position(val, true);
			assert(page->IsLeafLevel());
			assert(!page->IsFull());
		}

		page->InsertRow(val);
	}

	// Split the tree based on the value provided.
	//
	void BTree::Split(Value val)
	{
retrySplit:
		// Traverse the tree from the root and split along the way.
		//
		Page* page = GetGlobalBufferPool()->FindPage(m_rootPageID);
		Page* parentPage = nullptr;

traverse:
		if (!page->IsLeafLevel())
		{
			if (page->IsFull())
			{
				// We first need to split the internal tree and then retry splitting leaf level.
				// This needs to be implemented.
				// 
				assert(0);
				goto retrySplit;
			}
			else
			{
				// Find the child page.
				//
				parentPage = page;
				
				page = FindChildPage(page, val);

				goto traverse;
			}
		}
		else
		{
			assert(page->IsFull());

			Value firstVal = page->GetRow(0);
			Value lastVal = page->GetLastRow();
			if (IsRootLevel(page->GetLevel()))
			{
				m_rootLevel++;
				parentPage = GetGlobalBufferPool()->GetNewPage(m_rootLevel);
				m_rootPageID = parentPage->GetPageId();
				parentPage->InsertIndexRow(firstVal, page->GetPageId());
			}
			else
			{
				assert(parentPage != nullptr);
			}

			Page* newLeafPage = GetGlobalBufferPool()->GetNewPage(0);
			PageId newLeafPageId = newLeafPage->GetPageId();

			Value splitVal = TransferRows(page, newLeafPage);

			// Fix linkages.
			//
			
			parentPage->InsertIndexRow(splitVal+1, newLeafPage->GetPageId());
			newLeafPage->SetPrevPageId(page->GetPageId());
			page->SetNextPageId(newLeafPage->GetPageId());
		}
	}

	Page* BTree::FindChildPage(Page* page, Value val)
	{
		PageId childPageId = page->GetIndexRow(0)->pageID;

		for (unsigned int slot = 0; slot < page->GetSlotCount(); slot++)
		{
			IndexPagePayload* payload = page->GetIndexRow(slot);
			if (val > payload->beginKey)
			{
				childPageId = payload->pageID;
			}
			else
			{
				break;
			}
		}

		return GetGlobalBufferPool()->FindPage(childPageId);
	}

	Value BTree::TransferRows(Page* leftPage, Page* rightPage)
	{
		unsigned int splitPoint = leftPage->GetSlotCount()/2;
		Value splitVal = leftPage->GetRow(splitPoint);

		// Transfer rows from left page to right from the split point.
		//
		for (unsigned int slot = splitPoint + 1; slot < leftPage->GetSlotCount(); slot++)
		{
			Value slotVal = leftPage->GetRow(slot);
			rightPage->InsertRow(slotVal);
		}

		leftPage->SetSlotCount(splitPoint+1);

		return splitVal;
	}

	// Get the first key of the BTree.
	//
	Page* BTree::GetFirstLeafPage()
	{
		return Position(0, false);
	}

	// Traverse the tree to find the leaf page either for read or write.
	//
	Page* BTree::Position(Value val, bool forInsert)
	{
		Page* page = GetGlobalBufferPool()->FindPage(m_rootPageID);

traverse:
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
			// Traverse the tree.
			//
			page = FindChildPage(page, val);
			goto traverse;
		}

		return page;
	}

	// Get the next key of the tree given a key.
	// -1 is used to indicate end of scan.
	//
	Value BTree::GetRow(PageId* pageId, unsigned int* slot)
	{
		Page* page = GetGlobalBufferPool()->FindPage(*pageId);
		assert(page->IsLeafLevel());

		Value slotVal = -1;

nextPage:
		if (*slot < page->GetSlotCount())
		{
			slotVal = page->GetRow(*slot);
		}
		else if (page->GetNextPageId() != 0)
		{
			page = GetGlobalBufferPool()->FindPage(page->GetNextPageId());
			*pageId = page->GetPageId();
			*slot = 0;

			goto nextPage;
		}
		
		return slotVal;
	}

	// Initialize a session with the BTree.
	//
	BTreeSession::BTreeSession(BTree* btree)
	{
		m_btree = btree;
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
		Value nextVal = -1;

		nextVal = m_btree->GetRow(&m_currentPageId, &m_currentSlot);
		m_currentSlot++;

		if (nextVal == -1)
		{
			return false;
		}

		rgvals[0] = nextVal;
		return true;
	}
}