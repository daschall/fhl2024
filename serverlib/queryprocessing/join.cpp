#include "operators.h"

namespace Qp
{
	Join::Join(IOperator* left, IOperator* right, unsigned int clvals, unsigned int crvals, unsigned int lcol, unsigned int rcol)
		: left(left)
		, right(right)
		, clvals(clvals)
		, crvals(crvals)
		, lcol(lcol)
		, rcol(rcol)
	{
		lvals = new Value[clvals];
		rvals = new Value[crvals];
	}

	bool gotlrow = false;
	bool ropen = false;

	void Join::Open()
	{
		left->Open();
	}

	bool Join::GetRow(Value* rgvals)
	{
		while (true)
		{
			if (!gotlrow)
			{
				gotlrow = left->GetRow(lvals);

				if (!gotlrow)
				{
					// No more rows from left, we're done.
					//
					return false;
				}
			}

			if (!ropen)
			{
				right->Open();
				ropen = true;
			}

			while (right->GetRow(rvals))
			{
				// Got a row from left and right, join.
				//
				if (lvals[lcol] == rvals[rcol])
				{
					// We found matching rows, copy to output.
					//
					std::copy(lvals, lvals + clvals, rgvals);
					std::copy(rvals, rvals + crvals, rgvals + clvals);
					return true;
				}
			}

			// Right side is out of rows, move to next left row.
			//
			right->Close();
			ropen = false;
			gotlrow = false;
		}
	}

	void Join::Close()
	{
		if (ropen)
		{
			right->Close();
		}

		left->Close();
	}
}