/*
	This file contains BTree tests.
*/

#include "pch.h"

// Tests that the scanner that projects all rows from a tree.
//
TEST(BTreeSeTestSuite, BtreeInsertScan)
{
	// Create a value array to hold data.
	//
	const int nCols = 1;
	Value rgvals[nCols] = {};
	unsigned int totalRows = 2000;

	// Create a BTree with rows.
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

	btreeScanner.Open();
	while (btreeScanner.GetRow(rgvals))
	{
		EXPECT_EQ(numRows, rgvals[0]);
		++numRows;
	}
	btreeScanner.Close();

	EXPECT_EQ(totalRows, numRows);
}
