#include "join.h"

#include <algorithm>

namespace Qp
{
	Join::Join(IOperator* left, IOperator* right, unsigned int clvals, unsigned int crvals, JoinExpression expr)
		: left(left)
		, right(right)
		, clvals(clvals)
		, crvals(crvals)
		, expr(expr)
	{
		lvals = new Value[clvals];
		rvals = new Value[crvals];
	}

	void Join::Open()
	{
		left->Open();
	}

	bool Join::GetRow(Value* rgvals)
	{
		return false;
	}

	void Join::Close()
	{
		left->Close();
	}
}