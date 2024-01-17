/*
	This file contains more advanced query tests.
	You'll have to implement the query tree yourself for the given task.
*/

#include "pch.h"

#include "setup.h"

// Find all classes for teachers living in ZIP code 97010
//
// SELECT CourseId FROM Teachers T, Courses C WHERE T.zip = 97010 AND T.TeacherId = C.TeacherId
//
TEST_F(QueriesTestSuite, SelectClassesFromTeachersLinvingZip97010)
{
	Value rgvals[1];

	Value numRows = 0;
	ExecuteQuery(PDummyOp,
		rgvals,
		[&](Value *rgvals)
		{
			++numRows;

			if (numRows == 1)
				ValidateRow(rgvals, 1, 2001);
			if (numRows == 2)
				ValidateRow(rgvals, 1, 2003);
			if (numRows == 3)
				ValidateRow(rgvals, 1, 2004);
			if (numRows == 4)
				ValidateRow(rgvals, 1, 2008);
			if (numRows == 5)
				ValidateRow(rgvals, 1, 2010);
			if (numRows == 6)
				ValidateRow(rgvals, 1, 2014);
			if (numRows == 7)
				ValidateRow(rgvals, 1, 2015);
		});;


	EXPECT_EQ(7, numRows);
}

