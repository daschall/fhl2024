#include "common/value.h"
#include "btree.h"


#pragma once

namespace SE
{
	// A session operates on an index and stores progress of a scan.
	//
	class BTreeSession
	{
	public:
		BTreeSession(BTree* btree);

		// Implement storage interfaces for an index.
		//
		void Open();
		bool GetRow(Value* val);
		void Close() {}

	private:

		// Store progress of the scan.
		//
		PageId m_currentPageId;
		unsigned int m_currentSlot;
		BTree* m_btree;
	};
}