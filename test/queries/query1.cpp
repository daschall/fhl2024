/*
	This file contains more advanced query tests.
	You'll have to implement the query tree yourself for the given task.
*/

#include "pch.h"

#include "setup.h"

// Select the first 10 barely passing grades.
// 
// SELECT TOP 10 CourseId, StudentId, grade FROM grades WHERE grade >= 40 ORDER BY grade, CourseId, StudentId
//
TEST_F(QueriesTestSuite, SelectBadGradesByCourseAndStudent)
{
	Value rgvals[5];

	// FROM grades
	//
	SE::BTreeSession session(&Grades.BTree);
	Qp::BTreeScanner scanner(&session);

	// WHERE grade >= 40
	//
	Qp::Filter filter(&scanner, [=](Value *rgvals)
		{
			return rgvals[Grades.Columns.Grade] >= 40;
		});

	// ORDER BY grade, CourseId, StudentId
	//
	Qp::Sort sort(&filter, 5, [=](Value *l, Value *r)
		{
			if (l[Grades.Columns.Grade] != r[Grades.Columns.Grade])
			{
				return l[Grades.Columns.Grade] < r[Grades.Columns.Grade];
			};

			if (l[Grades.Columns.CourseId] != r[Grades.Columns.CourseId])
			{
				return l[Grades.Columns.CourseId] < r[Grades.Columns.CourseId];
			};

			return l[Grades.Columns.StudentId] < r[Grades.Columns.StudentId];
		});

	// SELECT courseId, studentId, grade
	//
	Qp::Project project(&sort, [=](Value *rgvals)
		{
			rgvals[0] = rgvals[Grades.Columns.CourseId];
			rgvals[1] = rgvals[Grades.Columns.StudentId];
			rgvals[2] = rgvals[Grades.Columns.Grade];
		});


	// TOP 10
	//
	Qp::Top top(&project, 10);

	Value numRows = 0;

	ExecuteQuery(&top,
		rgvals,
		[&](Value *rgvals)
		{
			++numRows;

			if (numRows == 1)
				ValidateRow(rgvals, 3, 2003, 10018, 40);
			if (numRows == 2)
				ValidateRow(rgvals, 3, 2004, 10048, 40);
			if (numRows == 3)
				ValidateRow(rgvals, 3, 2005, 10069, 40);
			if (numRows == 4)
				ValidateRow(rgvals, 3, 2006, 10066, 40);
			if (numRows == 5)
				ValidateRow(rgvals, 3, 2008, 10028, 40);
			if (numRows == 6)
				ValidateRow(rgvals, 3, 2008, 10071, 40);
			if (numRows == 7)
				ValidateRow(rgvals, 3, 2008, 10079, 40);
			if (numRows == 8)
				ValidateRow(rgvals, 3, 2008, 10087, 40);
			if (numRows == 9)
				ValidateRow(rgvals, 3, 2009, 10027, 40);
			if (numRows == 10)
				ValidateRow(rgvals, 3, 2009, 10034, 40);
		});;


	EXPECT_EQ(10, numRows);
}

