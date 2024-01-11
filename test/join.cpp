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
	Qp::Join join(&left, &right, 1, 1, [](Value* l, Value* r) { return l[0] == r[0]; });

	Value numRows = 0;

	join.Open();
	while (join.GetRow(rgvals))
	{
		++numRows;
		EXPECT_EQ(numRows, rgvals[0]);
		EXPECT_EQ(numRows, rgvals[1]);
	}
	join.Close();
	
	EXPECT_EQ(10, numRows);
}
// Tests the join operator with additional columns.
// These additional columns should not change when passing through the join.
//
TEST(JoinQpTestSuite, Join2)
{
	Value rgvals[4];
	rgvals[1] = 111;
	rgvals[3] = 333;

	Qp::RowGenerator left(1, 10, 1);
	Qp::RowGenerator right(1, 10, 1);
	Qp::Join join(&left, &right, 2, 2, [](Value* l, Value* r) { return l[0] == r[0]; });

	Value numRows = 0;

	join.Open();
	while (join.GetRow(rgvals))
	{
		++numRows;
		EXPECT_EQ(numRows, rgvals[0]);
		EXPECT_EQ(numRows, rgvals[2]);
		EXPECT_EQ(111, rgvals[1]);
		EXPECT_EQ(333, rgvals[3]);
	}
	join.Close();

	EXPECT_EQ(10, numRows);
}

// Tests the join operator with a not-equal predicate.
//
TEST(JoinQpTestSuite, Join3)
{
	Value rgvals[2];

	Qp::RowGenerator left(1, 10, 1);
	Qp::RowGenerator right(1, 10, 1);
	Qp::Join join(&left, &right, 1, 1, [](Value* l, Value* r) { return l[0] != r[0]; });

	Value numRows = 0;

	join.Open();
	while (join.GetRow(rgvals))
	{
		++numRows;
		EXPECT_NE(rgvals[0], rgvals[1]);
	}
	join.Close();

	EXPECT_EQ(90, numRows);
}

// Tests a cross product.
//
TEST(JoinQpTestSuite, Join4)
{
	Value rgvals[2];

	Qp::RowGenerator left(1, 10, 1);
	Qp::RowGenerator right(1, 10, 1);
	Qp::Join join(&left, &right, 1, 1, [](Value* l, Value* r) { return true; });

	Value numRows = 0;

	join.Open();
	while (join.GetRow(rgvals))
	{
		++numRows;
	}
	join.Close();

	EXPECT_EQ(100, numRows);
}

// Tests that the join operator works on multiple identical rows.
//
TEST(JoinQpTestSuite, Join5)
{
	Value rgvals[2];

	Qp::RowGenerator left(1, 10, 1, 2);
	Qp::RowGenerator right(1, 10, 1, 2);
	Qp::Join join(&left, &right, 1, 1, [](Value* l, Value* r) { return l[0] == r[0]; });

	Value numRows = 0;

	join.Open();
	while (join.GetRow(rgvals))
	{
		++numRows;
		EXPECT_EQ(rgvals[0], rgvals[1]);
	}
	join.Close();

	EXPECT_EQ(40, numRows);
}
