/*
	This file contains BTree tests.
*/

#include "pch.h"

#include "common/helper.h"

// Tests that the scanner that projects all rows from a tree.
//
TEST(BTreeSeTestSuite, BtreeProject)
{
	// Create a value array to hold data.
	//
	const int nCols = 1;
	Value rgvals[nCols] = {};
	unsigned int totalRows = 8000;

	// Create a BTree with 100 rows.
	//
	SE::BTree btree;

	for (Value i = 0; i < totalRows; i++)
	{
		btree.InsertRow(i);
	}

	// Create a session to iterate over the BTree created above.
	//
	SE::BTreeSession btreeSession(&btree);

	// Init the scan operator.
	//
	Qp::BTreeScanner btreeScanner(&btreeSession);

	Qp::Project project(&btreeScanner, [](Value* rgval) {});
	Value numRows = 0;

	project.Open();
	while (project.GetRow(rgvals))
	{
		EXPECT_EQ(numRows, rgvals[0]);
		++numRows;
	}
	project.Close();

	EXPECT_EQ(totalRows, numRows);
}


// Tests that the scanner filters rows from a tree.
//
TEST(BTreeSeTestSuite, BtreeFilter)
{
	// Create a value array to hold data.
	//
	const int nCols = 1;
	Value rgvals[nCols] = {};

	// Create a BTree with 100 rows.
	//
	SE::BTree btree;

	for (Value i = 0; i < 100; i++)
	{
		btree.InsertRow(i);
	}

	// Create a session to iterate over the BTree created above.
	//
	SE::BTreeSession btreeSession(&btree);

	// Init the scan operator.
	//
	Qp::BTreeScanner btreeScanner(&btreeSession);

	// Filter using above expression.
	//
	Qp::Filter filter(&btreeScanner, [](Value* rgvals) { return rgvals[0] == 5; });

	// Root of the query is the filter.
	//
	Qp::IOperator* root = &filter;


	// Now run the query until we get no more rows.
	//
	root->Open();
	while (root->GetRow(rgvals))
	{
		DumpValues(std::cout, rgvals, nCols);
	}
	root->Close();
}
