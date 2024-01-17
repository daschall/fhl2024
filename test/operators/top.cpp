/*
	This file contains QP tests for the Top operator.
*/

#include "pch.h"

// Tests that the Top operator only returns the given number of rows.
//
TEST(QpTestSuiteTop, TopN)
{
	Value rgvals[1];
	Qp::ConstScan rowGen(1, 100, 1);
	Qp::Top top(&rowGen, 10);
	Value numRows = 0;

	ExecuteQuery(&top,
		rgvals,
		[&](Value *rgvals)
		{
			++numRows;
			EXPECT_EQ(numRows, rgvals[0]);
		});

	EXPECT_EQ(10, numRows);
}

// Tests that the Top operator returns all rows if N is higher than the rowcount of the child.
//
TEST(QpTestSuiteTop, TopAllRows)
{
	Value rgvals[1];
	Qp::ConstScan rowGen(1, 5, 1);
	Qp::Top top(&rowGen, 10);
	Value numRows = 0;

	ExecuteQuery(&top,
		rgvals,
		[&](Value *rgvals)
		{
			++numRows;
			EXPECT_EQ(numRows, rgvals[0]);
		});

	EXPECT_EQ(5, numRows);
}

// Tests that the Top operator returns all rows if N is the same as the rowcount of the child.
//
TEST(QpTestSuiteTop, TopAllRows2)
{
	Value rgvals[1];
	Qp::ConstScan rowGen(1, 5, 1);
	Qp::Top top(&rowGen, 5);
	Value numRows = 0;

	ExecuteQuery(&top,
		rgvals,
		[&](Value *rgvals)
		{
			++numRows;
			EXPECT_EQ(numRows, rgvals[0]);
		});

	EXPECT_EQ(5, numRows);
}


// Tests that reopening the Top operator works.
//
TEST(QpTestSuiteTop, TopReopen)
{
	Value rgvals[1];
	Qp::ConstScan rowGen(1, 100, 1);
	Qp::Top top(&rowGen, 10);
	Value numRows = 0;

	ExecuteQuery(&top,
		rgvals,
		[&](Value *rgvals)
		{
			++numRows;
			EXPECT_EQ(numRows, rgvals[0]);
		});

	EXPECT_EQ(10, numRows);

	// Try again.
	//
	numRows = 0;

	ExecuteQuery(&top,
		rgvals,
		[&](Value *rgvals)
		{
			++numRows;
			EXPECT_EQ(numRows, rgvals[0]);
		});

	EXPECT_EQ(10, numRows);
}
