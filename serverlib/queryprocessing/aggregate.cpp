#include "aggregate.h"

#include <algorithm>

namespace Qp
{
	StreamAggregate::StreamAggregate(IOperator* child, unsigned int nvals, unsigned int groupByColumn, AggregateExpression aggExpression)
		: child(child)
		, nvals(nvals)
		, groupByColumn(groupByColumn)
		, aggExpression(aggExpression)
	{
		rgvalsChild = new Value[nvals];
	}

	void StreamAggregate::Open()
	{
		child->Open();
	}

	bool StreamAggregate::GetRow(Value* rgvals)
	{
		return false;
	}

	void StreamAggregate::Close()
	{
		child->Close();
	}
}