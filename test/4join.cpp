/*
	This file contains QP tests for the Join operator.
*/

#include "pch.h"

// Tests the join operator.
//
TEST(JoinQpTestSuite, Join1)
{
	Value rgvals[2];

	Qp::RowGenerator left(1, 10, 1);
	Qp::RowGenerator right(1, 10, 1);
	Qp::Join join(&left, &right, 1, 1, 0, 0);

	Value numRows = 0;

	while (join.GetRow(rgvals))
	{
		++numRows;
		EXPECT_EQ(numRows, rgvals[0]);
		EXPECT_EQ(numRows, rgvals[1]);
	}
  EXPECT_EQ(10, numRows);
}
// Tests the join operator with additional columns.
//
TEST(JoinQpTestSuite, Join2)
{
	Value rgvals[4];
	Qp::RowGenerator left(1, 10, 1);
	Qp::RowGenerator right(1, 10, 1);
	Qp::Join join(&left, &right, 2, 2, 0, 0);

	Value numRows = 0;

	while (join.GetRow(rgvals))
	{
		++numRows;
		EXPECT_EQ(numRows, rgvals[0]);
		EXPECT_EQ(numRows, rgvals[2]);
	}
	EXPECT_EQ(10, numRows);
}
