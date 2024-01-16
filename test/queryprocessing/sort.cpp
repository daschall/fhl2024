/*
	This file contains QP tests for the Sort operator.
*/

#include "pch.h"

// Tests the sort operator.
//
TEST(SortQpTestSuite, SortDescending)
{
	Qp::RowGenerator rowGen(1, 100, 1, 3);
	Qp::Sort sort(&rowGen, 1,
		[](Value* left, Value* right)
		{
			// sort descending
			//
			return left[0] > right[0];
		});

	Value rgvals[1];

	Value numRows = 0;
	Value lastRow = 999;

	sort.Open();
	while (sort.GetRow(rgvals))
	{
		// next row should be <= last row
		//
		EXPECT_LE(rgvals[0], lastRow);
		lastRow = rgvals[0];
		++numRows;
	}
	sort.Close();
	
	EXPECT_EQ(300, numRows);
}

// Tests the sort operator.
//
TEST(SortQpTestSuite, SortAscending)
{
	Qp::RowGenerator rowGen(1, 100, 1, 3);
	Qp::Sort sort(&rowGen, 1,
		[](Value* in, Value* out)
		{
			// sort ascending
			//
			return in[0] < out[0];
		});

	Value rgvals[1];

	Value numRows = 0;
	Value lastRow = 0;

	sort.Open();
	while (sort.GetRow(rgvals))
	{
		// next row should be >= last row
		//
		EXPECT_GE(rgvals[0], lastRow);
		lastRow = rgvals[0];
		++numRows;
	}
	sort.Close();

	EXPECT_EQ(300, numRows);
}