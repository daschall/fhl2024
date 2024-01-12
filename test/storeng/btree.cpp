/*
	This file contains BTree tests.
*/

#include "pch.h"

#include "common/helper.h"

// Tests that the scanner reads all the rows from the tree.
//
TEST(BTreeSeTestSuite, Btree1)
{
	// Create a value array to hold data.
	//
	const int nCols = 3;
	Value rgvals[nCols] = {};
	rgvals[2] = 20;

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
