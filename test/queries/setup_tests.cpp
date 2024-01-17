//
// setup_tests.cpp - This file contains tests to validate the tables have been properly loaded.
//

#include "pch.h"

#include "setup.h"

typedef QueriesTestSuite SetupTestSuite;

// Validates the first and last row of the Students table.
// 
TEST_F(SetupTestSuite, ValidateStudentsTable)
{
	Value rgvals[4];

	SE::BTreeSession session(&Students.BTree);
	Qp::BTreeScanner scanner(&session);

	Value numRows = 0;

	ExecuteQuery(&scanner,
		rgvals,
		[&](Value *rgvals)
		{
			++numRows;

			if (numRows == 1)
			{
				// Validate first student.
				//
				EXPECT_EQ(10001, rgvals[0]);
				EXPECT_EQ(20000101, rgvals[1]);
				EXPECT_EQ(98052, rgvals[2]);
				EXPECT_EQ(5551234, rgvals[3]);
			}

			if (numRows == 100)
			{
				// Validate last student.
				//
				EXPECT_EQ(10100, rgvals[0]);
				EXPECT_EQ(20041209, rgvals[1]);
				EXPECT_EQ(97160, rgvals[2]);
				EXPECT_EQ(5551382, rgvals[3]);
			}
		});;


	EXPECT_EQ(100, numRows);
}


// Validates the first and last row of the Teachers table.
// 
TEST_F(SetupTestSuite, ValidateTeachersTable)
{
	Value rgvals[4];

	SE::BTreeSession session(&Teachers.BTree);
	Qp::BTreeScanner scanner(&session);

	Value numRows = 0;

	ExecuteQuery(&scanner,
		rgvals,
		[&](Value *rgvals)
		{
			++numRows;

			if (numRows == 1)
			{
				// Validate first teacher.
				//
				EXPECT_EQ(50001, rgvals[0]);
				EXPECT_EQ(19450510, rgvals[1]);
				EXPECT_EQ(98052, rgvals[2]);
				EXPECT_EQ(5557897, rgvals[3]);
			}

			if (numRows == 5)
			{
				// Validate last teacher.
				//
				EXPECT_EQ(50005, rgvals[0]);
				EXPECT_EQ(19580620, rgvals[1]);
				EXPECT_EQ(97010, rgvals[2]);
				EXPECT_EQ(5555581, rgvals[3]);
			}
		});;


	EXPECT_EQ(5, numRows);
}

// Validates the first and last row of the Courses table.
// 
TEST_F(SetupTestSuite, ValidateCoursesTable)
{
	Value rgvals[3];

	SE::BTreeSession session(&Courses.BTree);
	Qp::BTreeScanner scanner(&session);

	Value numRows = 0;

	ExecuteQuery(&scanner,
		rgvals,
		[&](Value *rgvals)
		{
			++numRows;

			if (numRows == 1)
			{
				// Validate first course.
				//
				EXPECT_EQ(2001, rgvals[0]);
				EXPECT_EQ(50005, rgvals[1]);
				EXPECT_EQ(2, rgvals[2]);
			}

			if (numRows == 16)
			{
				// Validate last course.
				//
				EXPECT_EQ(2016, rgvals[0]);
				EXPECT_EQ(50001, rgvals[1]);
				EXPECT_EQ(2, rgvals[2]);
			}
		});;


	EXPECT_EQ(16, numRows);
}

// Validates the first and last row of the Grades table.
// 
TEST_F(SetupTestSuite, ValidateGradesTable)
{
	Value rgvals[5];

	SE::BTreeSession session(&Grades.BTree);
	Qp::BTreeScanner scanner(&session);

	Value numRows = 0;

	ExecuteQuery(&scanner,
		rgvals,
		[&](Value *rgvals)
		{
			++numRows;

			if (numRows == 1)
			{
				// Validate first grade.
				//
				EXPECT_EQ(1, rgvals[0]);
				EXPECT_EQ(10065, rgvals[1]);
				EXPECT_EQ(2009, rgvals[2]);
				EXPECT_EQ(20211118, rgvals[3]);
				EXPECT_EQ(36, rgvals[4]);
			}

			if (numRows == 3200)
			{
				// Validate last grade.
				//
				EXPECT_EQ(3200, rgvals[0]);
				EXPECT_EQ(10045, rgvals[1]);
				EXPECT_EQ(2003, rgvals[2]);
				EXPECT_EQ(20221203, rgvals[3]);
				EXPECT_EQ(36, rgvals[4]);
			}
		});;


	EXPECT_EQ(3200, numRows);
}