#pragma once

#include "common/value.h"


typedef void(*Expression)(Value*);

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
