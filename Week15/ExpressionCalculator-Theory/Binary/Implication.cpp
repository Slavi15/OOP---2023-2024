#include "Implication.h"

Implication::Implication(BooleanExpression* lhs, BooleanExpression* rhs) : BinaryOperation(lhs, rhs) {}

bool Implication::eval(const BooleanInterPretation& interpretation) const
{
	return !lhs->eval(interpretation) || rhs->eval(interpretation);
}

BooleanExpression* Implication::clone() const
{
	return new Implication(lhs->clone(), rhs->clone());
}
