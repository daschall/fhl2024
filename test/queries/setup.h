
#include "pch.h"

// This class contains some mock tables we'll use to run queries on.
//
class QueriesTestSuite : public testing::Test
{
public:
	//	Table Students
	// ------------
	//	StudentId		int
	//	dob				int [YYYYMMDD]
	//	zip				int
	//	phone			int
	//
	struct
	{
		SE::BTree BTree;
		struct
		{
			const unsigned int StudentId = 0;
			const unsigned int Dob = 1;
			const unsigned int Zip = 2;
			const unsigned int Phone = 3;
		} Columns;
		const unsigned int NumColumns = 4;
	} Students;

	//	Table Teachers
	// ------------
	//	TeacherId		int
	//	dob				int [YYYYMMDD]
	//	zip				int
	//	phone			int
	//
	struct
	{
		SE::BTree BTree;
		struct
		{
			const unsigned int TeacherId = 0;
			const unsigned int Dob = 1;
			const unsigned int Zip = 2;
			const unsigned int Phone = 3;
		} Columns;
		const unsigned int NumColumns = 4;
	} Teachers;

	//	Table Courses
	// ------------
	//	CourseId		int
	//	TeacherId		int
	//	level			int	[between 1 and 6]
	//
	struct
	{
		SE::BTree BTree;
		struct
		{
			const unsigned int CourseId = 0;
			const unsigned int TeacherId = 1;
			const unsigned int Level = 2;
		} Columns;
		const unsigned int NumColumns = 3;
	} Courses;

	//	Table Grades
	// ------------
	//	GradeId			int
	//	StudentId		int
	//	CourseId		int
	//	date			int	[YYYYMMDD]
	//	grade			int	[between 0 and 100, < 40 means failed]
	//
	struct
	{
		SE::BTree BTree;
		struct
		{
			const unsigned int GradeId = 0;
			const unsigned int StudentId = 1;
			const unsigned int CourseId = 2;
			const unsigned int Date = 3;
			const unsigned int Grade = 4;
		} Columns;
		const unsigned int NumColumns = 5;
	} Grades;

	DummyOperator *PDummyOp;
protected:
	void SetUp() override;
};
