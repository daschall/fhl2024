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
		return false;
	}

	void Top::Close()
	{
		child->Close();
	}
}