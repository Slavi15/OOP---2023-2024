#pragma once

#include "BinaryOperation.h"

class Conjunction : public BinaryOperation
{
public:
	Conjunction(BooleanExpression* lhs, BooleanExpression* rhs);

	bool eval(const BooleanInterPretation& interpretation) const override;

	BooleanExpression* clone() const override;
};