#pragma once

#include "interfaces/ioperator.h"
#include "interfaces/iexpression.h"

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
		BTreeScanner();

		void Open() override;
		bool GetRow(Value* rgvals) override;
		void Close() override;

	private:
	};


	// This operator only returns rows that match the predicate
	// and discards all other rows.
	//
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
	
	// This operator joins rows from two inputs on two given columns.
	// Only equi-join is supported, i.e. the column values in both
	// columns need to be equal to be considered a match.
	//
	// Since joins operate on two tables, you'll need to specify 
	// how many columns the left and right side returns.
	// The join will keep separate Value arrays for each child internally.
	//
	class Join : public IOperator
	{
	public:
		Join(IOperator* left, IOperator* right, unsigned int clvals, unsigned int rcvals, unsigned int lcol, unsigned int rcol);

		void Open() override;
		bool GetRow(Value* rgvals) override;
		void Close() override;

	private:
		IOperator* left;
		IOperator* right;
		unsigned int clvals;
		unsigned int crvals;
		unsigned int lcol;
		unsigned int rcol;
		Value* lvals;
		Value* rvals;
	};

}