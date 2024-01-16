/*
	This file contains QP tests for the Project operator.
*/

#include "pch.h"

// Tests that the project expression is called for every row.
//
TEST(ProjectQpTestSuite, Project1)
{
	Value rgvals[3];
	rgvals[1] = 0;
	Qp::ConstScan rowGen(1, 10, 1);
	Qp::Project project(&rowGen, [](Value* rgval)
		{
			// Increment the second column.
			//
			++rgval[1];
		});
	Value numRows = 0;

	project.Open();
	while (project.GetRow(rgvals))
	{
		++numRows;
		EXPECT_EQ(numRows, rgvals[0]);
		EXPECT_EQ(numRows, rgvals[1]);
	}
	project.Close();

	EXPECT_EQ(10, numRows);
}
