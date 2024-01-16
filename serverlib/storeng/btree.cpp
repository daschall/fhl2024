#include "btree.h"

#include "page.h"
#include "buffer.h"

namespace SE
{
	// Contructs basic tree structure with one page.
	//
	BTree::BTree()
	{
		m_rootLevel = 0;
		m_rootPageID = GetGlobalBufferPool()->GetNewPage(m_rootLevel)->GetPageId();
	}

	// Insert single row in ascending order.
	//
	void BTree::InsertRow(Value val)
	{
		// Find the insert point for the given value.
		//
		Page* page = Position(val, true);
		assert(page->IsLeafLevel());

		// Split the page if it is full.
		//
		if (page->IsFull())
		{
			Split(val);

			// Find new insert point after split.
			//
			page = Position(val, true);
			assert(page->IsLeafLevel());
			
		}

		// At this point, there should be space on the page.
		//
		assert(!page->IsFull());

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
		// Traverse the tree till we reach leaf level.
		//
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

				// Continue traversing the tree.
				//
				goto traverse;
			}
		}
		else
		{
			assert(page->IsFull());

			Value firstVal = page->GetRow(0);
			Value lastVal = page->GetLastRow();

			// If this is the initial root page case, increase the level of the tree.
			//
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

			// Create a new leaf page.
			//
			Page* newLeafPage = GetGlobalBufferPool()->GetNewPage(0);
			PageId newLeafPageId = newLeafPage->GetPageId();

			// Transfer some rows from old page to the newly created page.
			//
			Value splitVal = TransferRows(page, newLeafPage);

			// Insert the newly created page into the tree structure.
			// This involves fixing the linkages.
			//
			parentPage->InsertIndexRow(splitVal+1, newLeafPage->GetPageId());
			newLeafPage->SetPrevPageId(page->GetPageId());
			page->SetNextPageId(newLeafPage->GetPageId());
		}
	}

	// Given a index page, find the child page for the given value.
	//
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

	// Transfer rows from one page to another by choosing a split point.
	//
	Value BTree::TransferRows(Page* leftPage, Page* rightPage)
	{
		// This implementation chooses mid-point for split. Other points can be chosen.
		//
		unsigned int splitPoint = leftPage->GetSlotCount()/2;
		Value splitVal = leftPage->GetRow(splitPoint);

		// Transfer rows from left page to right from the split point.
		//
		for (unsigned int slot = splitPoint + 1; slot < leftPage->GetSlotCount(); slot++)
		{
			Value slotVal = leftPage->GetRow(slot);
			rightPage->InsertRow(slotVal);
		}

		// Set the number of rows on the old page.
		//
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
		// Provide the next row on the page if we're not at the end of it.
		//
		if (*slot < page->GetSlotCount())
		{
			slotVal = page->GetRow(*slot);
			(*slot)++;
		}
		// Move to the next leaf page.
		//
		else if (page->GetNextPageId() != 0)
		{
			page = GetGlobalBufferPool()->FindPage(page->GetNextPageId());
			*pageId = page->GetPageId();
			*slot = 0;

			goto nextPage;
		}
		
		return slotVal;
	}
}