#include "Var.h"

Var::Var(char ch) : ch(ch) {}

bool Var::eval(const BooleanInterPretation& interpretation) const
{
	return interpretation(ch);
}

void Var::populateVariables(BooleanInterPretation& interpretation) const
{
	interpretation.set(ch, true);
}

BooleanExpression* Var::clone() const
{
	return new Var(ch);
}
