#include "sort.h"

#include <algorithm>

namespace Qp
{
	Sort::Sort(IOperator* child, unsigned int nvals, CompareExpression cmp)
		: child(child)
		, nvals(nvals)
		, cmp(cmp)
	{
	}

	void Sort::Open()
	{
	}

	bool Sort::GetRow(Value* rgvals)
	{
		return false;
	}

	void Sort::Close()
	{
		for(Value * row : childRows)
		{
			delete[] row;
		}
		childRows.clear();
	}
}