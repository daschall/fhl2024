/*
	This file contains more advanced query tests.
	You'll have to implement the query tree yourself for the given task.
*/

#include "pch.h"

#include "setup.h"

// Find the class with the highest failure rate (grade < 40).
//
// Hint:
//	To calculate the failure rate using integers, I multiplied the value by 100 to give us percentages and work around
//	issues with rounding.
//
// SELECT TOP 2 CourseId, FailureRate FROM
//	(SELECT CourseId, 100 * SUM(CASE WHEN grade < 40 THEN 1 ELSE 0 END) / COUNT(*) AS FailureRate FROM grades GROUP BY CourseId) I
// ORDER BY FailureRate DESC
//
TEST_F(QueriesTestSuite, SelectCoursesWithHighestFailureRate)
{
	Value rgvals[2];

	Value numRows = 0;
	ExecuteQuery(PDummyOp,
		rgvals,
		[&](Value *rgvals)
		{
			++numRows;

			// Since they have the same failure rate, we can't guarantee order.
			//
			if(rgvals[0] == 2004)
				ValidateRow(rgvals, 2, 2004, 78);
			if (rgvals[0] == 2012)
				ValidateRow(rgvals, 2, 2012, 78);
		});;


	EXPECT_EQ(2, numRows);
}

