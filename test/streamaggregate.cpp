/*
	This file contains QP tests for the StreamAggregate operator.
*/

#include "pch.h"

// Tests the stream aggregate operator.
//
TEST(StreamAggregateQpTestSuite, StreamAgg1)
{
	Qp::RowGenerator rowGen(1, 10, 1, 10);
	Qp::StreamAggregate agg(&rowGen, 1, 0,
		[](Value* in, Value* out, bool firstRow)
		{
			if (firstRow)
			{
				out[0] = 0;
				out[1] = 0;
			}

			// Sum and count the rows.
			//
			out[0] += in[0];
			++out[1];
		});

	Value rgvals[2];

	Value numRows = 0;

	agg.Open();
	while (agg.GetRow(rgvals))
	{
		++numRows;

		// Every group should have a sum of 10 * value and a count of 10 rows.
		//
		EXPECT_EQ(numRows * 10, rgvals[0]);
		EXPECT_EQ(10, rgvals[1]);
	}
	agg.Close();
	
	EXPECT_EQ(10, numRows);
}