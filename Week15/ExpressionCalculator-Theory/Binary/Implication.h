#pragma once

#include "BinaryOperation.h"

class Implication : public BinaryOperation
{
public:
	Implication(BooleanExpression* lhs, BooleanExpression* rhs);

	bool eval(const BooleanInterPretation& interpretation) const override;

	BooleanExpression* clone() const override;
};