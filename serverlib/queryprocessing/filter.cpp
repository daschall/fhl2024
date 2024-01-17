#include "filter.h"

namespace Qp
{
	Filter::Filter(IOperator* child, BooleanExpression expr)
		: child(child)
		, expr(expr)
	{
	}

	void Filter::Open()
	{
		child->Open();
	}

	bool Filter::GetRow(Value* rgvals)
	{
		return false;
	}

	void Filter::Close()
	{
		child->Close();
	}
}