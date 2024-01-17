/*
	This file contains more advanced query tests.
	You'll have to implement the query tree yourself for the given task.
*/

#include "pch.h"

#include "setup.h"

// Calculate how many exams were taken per teacher.
//
// SELECT TeacherId, COUNT(*) FROM grades, Courses WHERE Grades.CourseId= courses.CourseId GROUP BY TeacherId ORDER BY TeacherId
//
TEST_F(QueriesTestSuite, SelectExamsPerTeacher)
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
				ValidateRow(rgvals, 2, 50001, 836);
			if (numRows == 16)
				ValidateRow(rgvals, 2, 50005, 1378);
		});;


	EXPECT_EQ(5, numRows);
}

