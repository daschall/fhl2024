#pragma once

#include "interfaces/iexpression.h"

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

template<ComparisonType CMP>
class Comparison : public IExpression
{
public:
	Comparison(unsigned int lhs, unsigned int rhs)
		: lhs(lhs)
		, rhs(rhs)
	{
	}

	bool Eval(Value* rgvals) override
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
};