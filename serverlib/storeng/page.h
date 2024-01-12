#include <iostream>
#include <vector>
#include <map>
#include <assert.h>
#include "common/value.h"

namespace SE
{
	// Page header stores metadata about the page.
	//
	class PageHeader
	{
	public:
		PageHeader(
			unsigned int pageID,
			unsigned int level)
			:
			m_pageID(pageID),
			m_level(level),
			m_slotCount(0)
		{}

		unsigned int GetSlotCount()
		{
			return m_slotCount;
		}

	protected:
		unsigned int m_pageID;

		// 0 is leaf.
		//
		unsigned int m_level;

		unsigned int m_slotCount;
	};

	const int PAGE_SIZE = 8192;
	const int PAGE_DATA_SIZE = PAGE_SIZE - sizeof(PageHeader);

	// Structure of a page includes the header and the data section.
	//
	class Page : public PageHeader
	{
	public:
		Page(
			unsigned int pageID,
			unsigned int level)
			:
			PageHeader(pageID, level)
		{
			// Zero out the page.
			//
			memset(m_data, 0, (unsigned int)(PAGE_DATA_SIZE));
		}

		unsigned int GetPageId()
		{
			return m_pageID;
		}

		bool IsLeafLevel()
		{
			return m_level == 0;
		}

		// Page interfaces to read/write rows.
		//
		Value GetRow(unsigned int slot);
		Value GetLastRow();
		void InsertRow(Value val);

	private:
		unsigned char m_data[PAGE_DATA_SIZE];
	};

	// Implementation of buffer pool to provide list of pages.
	//
	class BufferPool
	{
	public:
		BufferPool()
			:
			m_nextPageID(0)
		{}

		Page* GetNewPage(unsigned int level);
		Page* FindPage(unsigned int pageID);

	private:
		unsigned int m_nextPageID;
		std::map<int, Page*> m_pages;
	};

	// Singleton buffer pool.
	//
	BufferPool* GetGlobalBufferPool();
}