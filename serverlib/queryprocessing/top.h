#pragma once

#include "interfaces/ioperator.h"
#include "interfaces/iexpression.h"

namespace Qp
{
	// This operator only returns the first N rows.
	//
	class Top : public IOperator
	{
	public:
		Top(IOperator* child, unsigned int N);

		void Open() override;
		bool GetRow(Value* rgvals) override;
		void Close() override;

	private:
		IOperator* child;
		unsigned int N;
		unsigned int rowCount;
	};
}