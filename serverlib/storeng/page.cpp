#include "page.h"

namespace SE
{
	// Insert a key on the page.
	// Note that this does not take care of sort order yet.
	// It assumes rows are inserted in sorted order.
	//
	void Page::InsertRow(Value val)
	{
		assert (IsLeafLevel());

		if (sizeof(Value) * (m_slotCount + 1) >= PAGE_DATA_SIZE)
		{
			assert(0);
		}

		if (m_slotCount > 0)
		{
			Value prevVal = *((Value*)(m_data)+m_slotCount-1);
			assert(val > prevVal);
		}
		
		*((Value*)(m_data)+m_slotCount) = val;

		m_slotCount++;
	}

	// Get the row on the page given a slot.
	//
	Value Page::GetRow(unsigned int slot)
	{
		return *((Value*)(m_data)+slot);
	}

	// Get the last key value on the page. This helps with positioning.
	//
	Value Page::GetLastRow()
	{
		return *((Value*)(m_data)+m_slotCount - 1);
	}

	// Get a new page from buffer pool.
	// Init the level of btree as part of it.
	//
	Page* BufferPool::GetNewPage(
		unsigned int level)
	{
		Page* page = new Page(m_nextPageID, level);
		m_pages[m_nextPageID] = page;
		m_nextPageID++;

		return page;
	}

	// Find the page structure given the page ID.
	//
	Page* BufferPool::FindPage(
		unsigned int pageID)
	{
		assert(pageID < m_nextPageID);
		return m_pages[pageID];
	}

	// Singleton buffer pool.
	//
	static BufferPool bufferPool;

	BufferPool* GetGlobalBufferPool()
	{
		return &bufferPool;
	}
}