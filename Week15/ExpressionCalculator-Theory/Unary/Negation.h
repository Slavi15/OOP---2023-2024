#pragma once

#include "UnaryOperation.h"

class Negation : public UnaryOperation
{
public:
	Negation(BooleanExpression* expr);

	bool eval(const BooleanInterPretation& interpretation) const override;

	BooleanExpression* clone() const override;
};