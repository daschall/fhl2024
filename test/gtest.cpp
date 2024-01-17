//
// pch.cpp
//

#include "pch.h"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	::testing::FLAGS_gtest_death_test_style = "threadsafe";
	::testing::FLAGS_gtest_break_on_failure = true;
	return RUN_ALL_TESTS();
}

void ExecuteQuery(Qp::IOperator *root, Value *rgvals, ProjectExpression printExpression)
{
	root->Open();

	while (root->GetRow(rgvals))
	{
		if (printExpression)
		{
			printExpression(rgvals);
		}
	}

	root->Close();
}

void ValidateRow(Value *rgvalsActual, unsigned int nVals, Value val1, Value val2, Value val3, Value val4, Value val5, Value val6, Value val7, Value val8, Value val9, Value val10)
{
	EXPECT_EQ(val1, rgvalsActual[0]);
	if(nVals > 1)
		EXPECT_EQ(val2, rgvalsActual[1]);
	if (nVals > 2)
		EXPECT_EQ(val3, rgvalsActual[2]);
	if (nVals > 3)
		EXPECT_EQ(val4, rgvalsActual[3]);
	if (nVals > 4)
		EXPECT_EQ(val5, rgvalsActual[4]);
	if (nVals > 5)
		EXPECT_EQ(val6, rgvalsActual[5]);
	if (nVals > 6)
		EXPECT_EQ(val7, rgvalsActual[6]);
	if (nVals > 7)
		EXPECT_EQ(val8, rgvalsActual[7]);
	if (nVals > 8)
		EXPECT_EQ(val9, rgvalsActual[8]);
	if (nVals > 9)
		EXPECT_EQ(val10, rgvalsActual[9]);
}
