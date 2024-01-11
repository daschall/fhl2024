#include "page.h"

namespace SE
{
	void Page::InsertRow(Value val)
	{
		assert (IsLeafLevel());

		if (sizeof(Value) * (m_slotCount + 1) >= PAGE_DATA_SIZE)
		{
			assert(0);
		}

		*((Value*)(m_data)+m_slotCount) = val;

		m_slotCount++;
	}

	Value Page::GetRow(unsigned int slot)
	{
		return *((Value*)(m_data)+slot);
	}

	Value Page::GetLastRow()
	{
		return *((Value*)(m_data)+m_slotCount-1);
	}

	Page* BufferPool::GetNewPage(
		unsigned int level)
	{
		Page* page = new Page(m_nextPageID, level);
		m_pages[m_nextPageID] = page;
		m_nextPageID++;

		return page;
	}

	Page* BufferPool::FindPage(
		unsigned int pageID)
	{
		assert(pageID < m_nextPageID);
		return m_pages[pageID];
	}

	static BufferPool bufferPool;

	BufferPool* GetGlobalBufferPool()
	{
		return &bufferPool;
	}
}