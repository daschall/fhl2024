/*
	This file contains basic QP tests.
	They should pass with the minimal implementation already.
*/

#include "pch.h"

// Tests that the row generator generates numbers 0..10
//
TEST(BasicQpTestSuite, RowGenerator)
{
	Value rgvals[1];
	Qp::RowGenerator rowGen(0, 10, 1);

	Value numRows = 0;

	while (rowGen.GetRow(rgvals))
	{
		++numRows;
		EXPECT_EQ(numRows-1, rgvals[0]);
	}
  EXPECT_EQ(11, numRows);
}

// Tests that the row generator generates even numbers between -20..20
//
TEST(BasicQpTestSuite, RowGenerator2)
{
	Value rgvals[1];
	Qp::RowGenerator rowGen(-20, 20, 2);

	Value numRows = 0;

	while (rowGen.GetRow(rgvals))
	{
		++numRows;
		EXPECT_EQ(-22 + numRows * 2, rgvals[0]);
	}
	EXPECT_EQ(21, numRows);
}

// Tests that the row generator generates odd numbers between -19..19
//
TEST(BasicQpTestSuite, RowGenerator3)
{
	Value rgvals[1];
	Qp::RowGenerator rowGen(-19, 20 /* 20 is not expected to be returned */, 2);

	Value numRows = 0;

	while (rowGen.GetRow(rgvals))
	{
		++numRows;
		EXPECT_EQ(-21 + numRows * 2, rgvals[0]);
	}
	EXPECT_EQ(20, numRows);
}