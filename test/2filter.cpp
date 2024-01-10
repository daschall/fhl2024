/*
	This file contains QP tests for the Filter operator.
*/

#include "pch.h"
#include <expressions/expressions.h>

// Tests that the filter only returns rows equal to 5
//
TEST(FilterQpTestSuite, Filter1)
{
	Value rgvals[2];
	rgvals[1] = 5;

	Comparison<ComparisonType::EQ> cmp(0, 1);

	Qp::RowGenerator rowGen(0, 10, 1);
	Qp::Filter filter(&rowGen, &cmp);

	Value numRows = 0;

	while (filter.GetRow(rgvals))
	{
		++numRows;
		EXPECT_EQ(5, rgvals[0]);
	}
  EXPECT_EQ(1, numRows);
}


// Tests that the filter only returns rows greater than 5
//
TEST(FilterQpTestSuite, Filter2)
{
	Value rgvals[2];
	rgvals[1] = 5;

	Comparison<ComparisonType::GT> cmp(0, 1);

	Qp::RowGenerator rowGen(0, 10, 1);
	Qp::Filter filter(&rowGen, &cmp);

	Value numRows = 0;

	while (filter.GetRow(rgvals))
	{
		++numRows;
		EXPECT_EQ(5 + numRows, rgvals[0]);
	}
	EXPECT_EQ(5, numRows);
}

// Tests that the filter does not return any rows
//
TEST(FilterQpTestSuite, Filter3)
{
	Value rgvals[2];
	rgvals[1] = 999;

	Comparison<ComparisonType::EQ> cmp(0, 1);

	Qp::RowGenerator rowGen(0, 10, 1);
	Qp::Filter filter(&rowGen, &cmp);

	Value numRows = 0;

	while (filter.GetRow(rgvals))
	{
		++numRows;
		FAIL("Should not have returned a row");
	}
	EXPECT_EQ(0, numRows);
}
