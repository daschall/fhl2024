#pragma once

#include "common/value.h"

class IExpression
{
public:
	virtual bool Eval(Value* rgvals) = 0;
};
