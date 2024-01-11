#pragma once

#include "common/value.h"


// A project expression takes a row and modifies any values.
//
typedef void(*ProjectExpression)(Value*);

// A boolean expression evaluates an expression on a row and returns
// whether the expression is true or false for that row.
//
typedef bool(*BooleanExpression)(Value*);

// A join expression takes two rows (left and right) as input
// and returns whether they are a match.
//
typedef bool(*JoinExpression)(Value*, Value*);

// An aggregate expression takes an input row and and an output row and
// aggregates the input row into the output row.
// A bool param indicates whether the aggregation is (re)starting,
// in which case the aggregate expression needs to reset its values to start again at 0.
//
typedef void(*AggregateExpression)(Value*, Value*, bool);

// A compare expression compares two rows and returns whether the first sorts lower than the second.
//
typedef bool(*CompareExpression)(Value*, Value*);
