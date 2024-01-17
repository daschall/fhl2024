#include "top.h"

#include <algorithm>

namespace Qp
{
	Top::Top(IOperator* child, unsigned int N)
		: child(child)
		, N(N)
		, rowCount(0)
	{
	}

	void Top::Open()
	{
		rowCount = 0;
		child->Open();
	}

	bool Top::GetRow(Value* rgvals)
	{
		if (rowCount >= N)
		{
			return false;
		}

		bool ret = child->GetRow(rgvals);
		++rowCount;

		return ret;
	}

	void Top::Close()
	{
		child->Close();
	}
}