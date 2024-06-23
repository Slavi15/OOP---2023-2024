#include "Conjunction.h"

Conjunction::Conjunction(BooleanExpression* lhs, BooleanExpression* rhs) : BinaryOperation(lhs, rhs) {}

bool Conjunction::eval(const BooleanInterPretation& interpretation) const
{
	return lhs->eval(interpretation) && rhs->eval(interpretation);
}

BooleanExpression* Conjunction::clone() const
{
	return new Conjunction(lhs->clone(), rhs->clone());
}
