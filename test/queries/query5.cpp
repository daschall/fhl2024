/*
	This file contains more advanced query tests.
	You'll have to implement the query tree yourself for the given task.
*/

#include "pch.h"

#include "setup.h"

// Calculate how many passing exams were taken per class.
//
// SELECT CourseId, COUNT(*) FROM grades WHERE grade >= 40 GROUP BY CourseId ORDER BY CourseId
//
TEST_F(QueriesTestSuite, SelectPassingExamsPerClass)
{
	Value rgvals[2];

	Value numRows = 0;
	ExecuteQuery(PDummyOp,
		rgvals,
		[&](Value *rgvals)
		{
			++numRows;

			// Only validate first and last row.
			//
			if (numRows == 1)
				ValidateRow(rgvals, 2, 2001, 51);
			if (numRows == 16)
				ValidateRow(rgvals, 2, 2016, 64);
		});;


	EXPECT_EQ(16, numRows);
}

