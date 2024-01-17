//
// pch.h
//

#pragma once

#include "gtest/gtest.h"

#include <cstdarg>

// For simplicity, include all SE/QP headers here.
//

#include "storeng/btreesession.h"
#include "storeng/btree.h"

#include "queryprocessing/aggregate.h"
#include "queryprocessing/btreescanner.h"
#include "queryprocessing/constscan.h"
#include "queryprocessing/filter.h"
#include "queryprocessing/join.h"
#include "queryprocessing/project.h"
#include "queryprocessing/sort.h"
#include "queryprocessing/top.h"


// Executes a query and runs the expression for every row returned.
// You need to pass an adequately sized Value* array.
// The expression can be anything, it can print the rows, it can count, it can have other side effects.
//
void ExecuteQuery(Qp::IOperator *root, Value *rgvals, ProjectExpression expression = nullptr);


// Validates that a row has all expected values.
// Note:
//	This would have been a cool variadic function, but the caveat is,
//	the expected values passed in need to be typed to Value, otherwise,
//	the compiler would randomly pass int and long long, and we wouldn't be able to distinguish.
//
void ValidateRow(Value *rgvalsActual, unsigned int nVals, Value val1, Value val2 = 0, Value val3 = 0, Value val4 = 0, Value val5 = 0, Value val6 = 0, Value val7 = 0, Value val8 = 0, Value val9 = 0, Value val10 = 0);

// Dummy operator that returns no rows.
// Used to make the tests fail instead of crash.
//
class DummyOperator : public Qp::IOperator
{
public:
	void Open() override {}
	bool GetRow(Value *) override { return false; }
	void Close() override {}
};