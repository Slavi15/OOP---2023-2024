#include "Negation.h"

Negation::Negation(BooleanExpression* expr) : UnaryOperation(expr) {}

bool Negation::eval(const BooleanInterPretation& interpretation) const
{
	return !expr->eval(interpretation);
}

BooleanExpression* Negation::clone() const
{
	return new Negation(expr->clone());
}
