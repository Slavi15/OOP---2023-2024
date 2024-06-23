#include "Disjunction.h"

Disjunction::Disjunction(BooleanExpression* lhs, BooleanExpression* rhs) : BinaryOperation(lhs, rhs) {}

bool Disjunction::eval(const BooleanInterPretation& interpretation) const
{
	return lhs->eval(interpretation) || rhs->eval(interpretation);
}

BooleanExpression* Disjunction::clone() const
{
	return new Disjunction(lhs->clone(), rhs->clone());
}
