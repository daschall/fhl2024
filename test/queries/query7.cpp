/*
	This file contains more advanced query tests.
	You'll have to implement the query tree yourself for the given task.
*/

#include "pch.h"

#include "setup.h"

// Find the easiest course (with the highest grade average of all passing grades).
//
// Hint:
//	AVG has to be implementing using SUM and COUNT followed by a Project.
//
// SELECT TOP 1 CourseId, AVG(grade) FROM grades WHERE grade >= 40 GROUP BY CourseId ORDER BY AVG(grade) DESC
//
TEST_F(QueriesTestSuite, SelectEasiestCourses)
{
	Value rgvals[2];

	Value numRows = 0;
	ExecuteQuery(PDummyOp,
		rgvals,
		[&](Value *rgvals)
		{
			++numRows;

			// Should be only one row.
			//
			ValidateRow(rgvals, 2, 2012, 72);
		});;


	EXPECT_EQ(1, numRows);
}

