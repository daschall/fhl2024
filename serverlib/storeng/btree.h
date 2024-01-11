#include "page.h"
#include "common/value.h"
#include "interfaces/istorage.h"

namespace SE
{
	class BTree
	{
	public:
		BTree()
		{
			m_rootLevel = 0;
			m_rootPageID = GetGlobalBufferPool()->GetNewPage(m_rootLevel)->GetPageId();
		}

		Value Open();
		Value GetNextRow(Value val);
		void Close()
		{

		}

		void InsertRow(Value val);

	private:
		Page* Position(Value val, bool forInsert);

		unsigned int m_rootPageID;
		unsigned int m_rootLevel;
	};

	class BTreeSession: public IStorage
	{
	public:
		BTreeSession(BTree* btree);
		void Open();
		bool GetRow(Value* val);
		void Close()
		{

		}
	private:

		Value m_lastKey;
		bool m_firstRowReturned;
		BTree* m_btree;
	};
}