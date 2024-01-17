#include "project.h"

#include <algorithm>

namespace Qp
{
	Project::Project(IOperator* child, ProjectExpression expr)
		: child(child)
		, expr(expr)
	{
	}

	void Project::Open()
	{
		child->Open();
	}

	bool Project::GetRow(Value* rgvals)
	{
		return false;
	}

	void Project::Close()
	{
		child->Close();
	}
}