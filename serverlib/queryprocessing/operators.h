#pragma once

#include "interfaces/ioperator.h"
#include "interfaces/iexpression.h"
#include "interfaces/istorage.h"

#include <vector>

namespace Qp
{
	// This operator generates values between [min..max] at step interval.
	//
	class RowGenerator : public IOperator
	{
	public:
		RowGenerator(Value min, Value max, Value step);

		void Open() override;

		bool GetRow(Value* rgvals) override;

		void Close() override;

	private:
		Value cur;
		Value max;
		Value min;
		Value step;
	};

	class BTreeScanner : public IOperator
	{
	public:
		BTreeScanner(SE::IStorage* storage);

		void Open() override;
		bool GetRow(Value* rgvals) override;
		void Close() override;

	private:
		SE::IStorage* m_storage;
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