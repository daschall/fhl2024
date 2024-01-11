#pragma once

#include "interfaces/ioperator.h"
#include "interfaces/iexpression.h"

#include <deque>

namespace Qp
{
	// This operator generates values between [min..max] at step interval.
	//
	class RowGenerator : public IOperator
	{
	public:
		RowGenerator(Value min, Value max, Value step, unsigned int repeat = 1);

		void Open() override;

		bool GetRow(Value* rgvals) override;

		void Close() override;

	private:
		Value cur;
		Value max;
		Value min;
		Value step;
		unsigned int repeat;

		unsigned int repeatCounter;
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
		Filter(IOperator *child, BooleanExpression expr);

		void Open() override;
		bool GetRow(Value* rgvals) override;
		void Close() override;

	private:
		IOperator* child;
		BooleanExpression expr;
	};

	class Project : public IOperator
	{
	public:
		Project(IOperator* child, ProjectExpression expr);

		void Open() override;
		bool GetRow(Value* rgvals) override;
		void Close() override;

	private:
		IOperator* child;
		ProjectExpression expr;
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
		Join(IOperator* left, IOperator* right, unsigned int clvals, unsigned int rcvals, JoinExpression expr);

		void Open() override;
		bool GetRow(Value* rgvals) override;
		void Close() override;

	private:
		IOperator* left;
		IOperator* right;
		unsigned int clvals;
		unsigned int crvals;
		JoinExpression expr;
		Value* lvals;
		Value* rvals;

		bool gotlrow;
		bool ropen;
	};

	// An aggregate aggregates rows using the aggregateExpr
	// grouped by the column value in the matchColumn.
	// A stream aggregate requires the rows to be sorted on matchColumn.
	//
	class StreamAggregate : public IOperator
	{
	public:
		StreamAggregate(IOperator* child, unsigned int nvals, unsigned int groupByColumn, AggregateExpression aggExpression);

		void Open() override;
		bool GetRow(Value* rgvals) override;
		void Close() override;

	private:
		IOperator* child;
		Value* rgvalsChild;
		unsigned int nvals;
		unsigned int groupByColumn;
		AggregateExpression aggExpression;
		bool pendingChildRow;
		bool childDone;
	};

	// Sort operator that orders all data using a compare expression.
	//
	class Sort : public IOperator
	{
	public:
		Sort(IOperator* child, unsigned int nvals, CompareExpression cmp);

		void Open() override;
		bool GetRow(Value* rgvals) override;
		void Close() override;

	private:
		IOperator* child;
		unsigned int nvals;
		CompareExpression cmp;

		std::deque<Value*> childRows;
		bool firstGetRow;
	};
}