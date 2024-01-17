/*
	This file contains more advanced query tests.
	You'll have to implement the query tree yourself for the given task.
*/

#include "pch.h"

#include "setup.h"

// Find zip codes where both teachers and students live
// Hint:
//	You'll have to DISTINCT your results, otherwise the same zip code might show up multiple times.
//	That can be done with an aggregation.
//
// SELECT DISTINCT S.zip FROM Students S, Teachers T WHERE S.zip = T.zip
//
TEST_F(QueriesTestSuite, SelectZipsWithTeachersAndStudents)
{
	Value rgvals[1];

	Value numRows = 0;
	ExecuteQuery(PDummyOp,
		rgvals,
		[&](Value *rgvals)
		{
			++numRows;

			if (numRows == 1)
				ValidateRow(rgvals, 1, 97010);
			if (numRows == 2)
				ValidateRow(rgvals, 1, 98052);
		});;


	EXPECT_EQ(2, numRows);
}

