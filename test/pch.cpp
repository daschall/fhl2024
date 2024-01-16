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
