/*
	This file contains QP tests for the BTreeScanner operator.
*/

#include "pch.h"

// Tests that the scanner reads all the rows from the tree.
//
TEST(BTreeScannerQpTestSuite, Scanner1)
{
	Value rgvals[1];

	Qp::BTreeScanner scanner(nullptr);

	Value numRows = 0;

	scanner.Open();
	while (scanner.GetRow(rgvals))
	{
		++numRows;
		EXPECT_EQ(numRows, rgvals[0]);
	}
	scanner.Close();

	EXPECT_EQ(100, numRows);
}
