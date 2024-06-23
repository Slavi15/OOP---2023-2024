#pragma once

#include "BinaryOperation.h"

class Disjunction : public BinaryOperation
{
public:
	Disjunction(BooleanExpression* lhs, BooleanExpression* rhs);

	bool eval(const BooleanInterPretation& interpretation) const override;

	BooleanExpression* clone() const override;
};