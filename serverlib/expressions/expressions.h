#pragma once

#include "interfaces/iexpression.h"

// Adds two row values and stores the result in a(nother) value.
// Note that all three columns can be the same.
//
class Addition : public IExpression
{
public:
	Addition(unsigned int iSum, unsigned int lhs, unsigned int rhs)
		: iSum(iSum)
		, lhs(lhs)
		, rhs(rhs)
	{
	}

	bool Eval(Value* rgvals) override
	{
		return
			rgvals[iSum] = rgvals[lhs] + rgvals[rhs];
	}

private:
	unsigned int iSum;
	unsigned int lhs;
	unsigned int rhs;
};

enum class ComparisonType
{
	LT,
	LE,
	EQ,
	GE,
	GT,
	NE
};

// Compares two row values and returns the result.
// Optionally stores the result in another column.
//
template<ComparisonType CMP>
class Comparison : public IExpression
{
public:
	Comparison(unsigned int lhs, unsigned int rhs, unsigned int result = -1)
		: lhs(lhs)
		, rhs(rhs)
		, result(result)
	{
	}

	bool Eval(Value* rgvals) override
	{
		bool res = InternalEval(rgvals);

		if (result != -1)
		{
			rgvals[result] = res;
		}

		return res;
	}

private:
	bool InternalEval(Value* rgvals)
	{
		if constexpr (CMP == ComparisonType::LT)
		{
			return
				rgvals[lhs] < rgvals[rhs];
		}
		if constexpr (CMP == ComparisonType::LE)
		{
			return
				rgvals[lhs] <= rgvals[rhs];
		}
		if constexpr (CMP == ComparisonType::EQ)
		{
			return
				rgvals[lhs] == rgvals[rhs];
		}
		if constexpr (CMP == ComparisonType::GE)
		{
			return
				rgvals[lhs] >= rgvals[rhs];
		}
		if constexpr (CMP == ComparisonType::GT)
		{
			return
				rgvals[lhs] > rgvals[rhs];
		}
		if constexpr (CMP == ComparisonType::NE)
		{
			return
				rgvals[lhs] != rgvals[rhs];
		}
	}

private:
	unsigned int lhs;
	unsigned int rhs;
	unsigned int result;
};