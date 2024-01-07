#include "operators.h"

namespace Qp
{
	RowGenerator::RowGenerator(Value min, Value max, Value step)
		: min(min)
		, max(max)
		, step(step)
		, cur(min)
	{}

	void RowGenerator::Open()
	{
		cur = min;
	}

	bool RowGenerator::GetRow(Value* rgvals)
	{
		if (cur <= max)
		{
			rgvals[0] = cur;
			cur += step;
			return true;
		}
		else
		{
			return false;
		}
	}

	void RowGenerator::Close()
	{}

	BTreeScanner::BTreeScanner()
	{
	}

	void BTreeScanner::Open()
	{}

	bool BTreeScanner::GetRow(Value* rgvals)
	{
		return false;
	}

	void BTreeScanner::Close()
	{}


	Filter::Filter(IOperator* child, IExpression* expr)
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
		do
		{
			if (!child->GetRow(rgvals))
			{
				return false;
			}

			if (expr->Eval(rgvals))
			{
				return true;
			}
		} while (true);
	}

	void Filter::Close()
	{
		child->Close();
	}
}