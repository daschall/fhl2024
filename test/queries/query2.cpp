/*
	This file contains more advanced query tests.
	You'll have to implement the query tree yourself for the given task.
*/

#include "pch.h"

#include "setup.h"

// Find the youngest student (and calculate their age in years as of 2024/01/17).
//
// Hint:
//	The age calculation should be a lot simpler in C++ than in SQL :)
//
// SELECT TOP 1 StudentId, dob,
// DATEDIFF(year,
// 	DATEADD(day, dob % 100 - 1,
// 		DATEADD(month, dob / 100 % 100 - 1,
// 			DATEADD(year, dob / 100 / 100 - 2000,
// 				'2000-01-01'))),
// 	'2024-01-17') AS age
// 	FROM Students ORDER BY dob DESC
//
TEST_F(QueriesTestSuite, SelectYoungestStudentAndAge)
{
	Value rgvals[3];

	Value numRows = 0;
	ExecuteQuery(PDummyOp,
		rgvals,
		[&](Value *rgvals)
		{
			++numRows;

			if (numRows == 1)
				ValidateRow(rgvals, 3, 10006, 20050711, 19);
		});;


	EXPECT_EQ(1, numRows);
}

