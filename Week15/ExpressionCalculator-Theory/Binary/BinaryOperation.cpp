#include "BinaryOperation.h"

BinaryOperation::BinaryOperation(BooleanExpression* lhs, BooleanExpression* rhs) : lhs(lhs), rhs(rhs) {}

void BinaryOperation::populateVariables(BooleanInterPretation& interpretation) const
{
	lhs->populateVariables(interpretation);
	rhs->populateVariables(interpretation);
}

BinaryOperation::~BinaryOperation() noexcept
{
	delete lhs;
	delete rhs;
}
