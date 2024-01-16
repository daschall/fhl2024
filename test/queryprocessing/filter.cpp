/*
	This file contains QP tests for the Filter operator.
*/

#include "pch.h"

// Tests that the filter only returns rows equal to 5
//
TEST(FilterQpTestSuite, Filter1)
{
	Value rgvals[1];

	Qp::RowGenerator rowGen(0, 10, 1);
	Qp::Filter filter(&rowGen, [](Value* rgvals) { return rgvals[0] == 5; });

	Value numRows = 0;

	filter.Open();
	while (filter.GetRow(rgvals))
	{
		++numRows;
		EXPECT_EQ(5, rgvals[0]);
	}
	filter.Close();

	EXPECT_EQ(1, numRows);
}


// Tests that the filter only returns rows greater than 5
//
TEST(FilterQpTestSuite, Filter2)
{
	Value rgvals[1];

	Qp::RowGenerator rowGen(0, 10, 1);
	Qp::Filter filter(&rowGen, [](Value* rgvals) { return rgvals[0] > 5; });

	Value numRows = 0;

	filter.Open();
	while (filter.GetRow(rgvals))
	{
		++numRows;
		EXPECT_EQ(5 + numRows, rgvals[0]);
	}
	filter.Close();

	EXPECT_EQ(5, numRows);
}

// Tests that the filter does not return any rows
//
TEST(FilterQpTestSuite, Filter3)
{
	Value rgvals[2];

	Qp::RowGenerator rowGen(0, 10, 1);
	Qp::Filter filter(&rowGen, [](Value* rgvals) { return rgvals[0] == 999; });

	Value numRows = 0;

	filter.Open();
	while (filter.GetRow(rgvals))
	{
		++numRows;
	}
	filter.Close();

	EXPECT_EQ(0, numRows);
}
