#include "operators.h"

namespace Qp
{
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