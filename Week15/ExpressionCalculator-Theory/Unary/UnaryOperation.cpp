#include "UnaryOperation.h"

UnaryOperation::UnaryOperation(BooleanExpression* expr) : expr(expr) {}

void UnaryOperation::populateVariables(BooleanInterPretation& interpretation) const
{
	expr->populateVariables(interpretation);
}

UnaryOperation::~UnaryOperation() noexcept
{
	delete expr;
}
