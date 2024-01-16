#include "page.h"

namespace SE
{
	// Check if page has no more space left.
	//
	bool Page::IsFull()
	{
		assert(IsLeafLevel());

		if (IsLeafLevel())
		{
			return (sizeof(Value) * (m_slotCount + 1) >= PAGE_DATA_SIZE);
		}
		else
		{
			return (sizeof(IndexPagePayload) * (m_slotCount + 1) >= PAGE_DATA_SIZE);
		}
	}

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
		

		*((Value*)((m_data)+(m_slotCount*sizeof(Value)))) = val;

		m_slotCount++;
	}

	void Page::InsertIndexRow(Value beginVal, PageId pageId)
	{
		assert(!IsLeafLevel());

		IndexPagePayload* newRecord = (IndexPagePayload *)(m_data + (m_slotCount * sizeof(IndexPagePayload)));

		newRecord->beginKey = beginVal;
		newRecord->pageID = pageId;

		m_slotCount++;
	}

	// Get the row on the page given a slot.
	//
	Value Page::GetRow(unsigned int slot)
	{
		return *((Value*)((m_data)+(slot*sizeof(Value))));
	}

	IndexPagePayload* Page::GetIndexRow(unsigned int slot)
	{
		assert(!IsLeafLevel());

		return (IndexPagePayload*)(m_data + (m_slotCount * sizeof(IndexPagePayload)));

	}

	// Get the last key value on the page. This helps with positioning.
	//
	Value Page::GetLastRow()
	{
		return *((Value*)((m_data)+((m_slotCount -1) * sizeof(Value))));
	}
}