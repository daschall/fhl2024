#pragma once

#include "interfaces/ioperator.h"
#include "interfaces/iexpression.h"

#include <vector>

namespace Qp
{
	class RowGenerator : public IOperator
	{
	public:
		RowGenerator(Value min, Value max, Value step)
		: min(min)
		, max(max)
		, step(step)
		, cur(0)
		{}

		void Open() override
		{
			cur = 0;
		}

		bool GetRow(Value* rgvals) override
		{
			if (cur < max)
			{
				rgvals[0] = cur;
				cur+=step;
				return true;
			}
			else
			{
				return false;
			}
		}

		void Close() override
		{}

	private:
		Value cur;
		Value max;
		Value min;
		Value step;
	};

	class BTreeScanner : public IOperator
	{
	public:
		BTreeScanner();

		void Open() override;
		bool GetRow(Value* rgvals) override;
		void Close() override;

	private:
	};


	class Filter : public IOperator
	{
	public:
		Filter(IOperator *child, IExpression* expr);

		void Open() override;
		bool GetRow(Value* rgvals) override;
		void Close() override;

	private:
		IExpression* expr;
		IOperator* child;
	};

	class Project : public IOperator
	{
	public:
		Project(IOperator* child);

		void Open() override;
		bool GetRow(Value* rgvals) override;
		void Close() override;

	private:
		IOperator* child;
	};

}