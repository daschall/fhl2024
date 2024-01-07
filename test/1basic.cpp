/*
	This file contains basic QP tests.
	They should pass with the minimal implementation already.
*/

#include "pch.h"

// Tests that the row generator generates numbers 0..10
//
TEST(BasicQpTestSuite, RowGenerator) {
	Value rgvals[1];
	Qp::RowGenerator rowGen(0, 10, 1);

	Value i = -1;

	while (rowGen.GetRow(rgvals))
	{
		++i;
		EXPECT_EQ(i, rgvals[0]);
	}
  EXPECT_EQ(10, i);
}

// Tests that the row generator generates even numbers between -20..20
//
TEST(BasicQpTestSuite, RowGenerator2) {
	Value rgvals[1];
	Qp::RowGenerator rowGen(-20, 20, 2);

	Value i = -22;

	while (rowGen.GetRow(rgvals))
	{
		i += 2;
		EXPECT_EQ(i, rgvals[0]);
	}
	EXPECT_EQ(20, i);
}

// Tests that the row generator generates odd numbers between -19..19
//
TEST(BasicQpTestSuite, RowGenerator3) {
	Value rgvals[1];
	Qp::RowGenerator rowGen(-19, 20 /* 20 is not expected to be returned */, 2);

	Value i = -21;

	while (rowGen.GetRow(rgvals))
	{
		i += 2;
		EXPECT_EQ(i, rgvals[0]);
	}
	EXPECT_EQ(19, i);
}