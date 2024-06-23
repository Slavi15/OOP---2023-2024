#pragma once

#include "../BooleanExpression.h"

class BinaryOperation : public BooleanExpression
{
protected:
	BooleanExpression* lhs = nullptr;
	BooleanExpression* rhs = nullptr;

public:
	BinaryOperation(BooleanExpression* lhs, BooleanExpression* rhs);

	void populateVariables(BooleanInterPretation& interpretation) const override;

	~BinaryOperation() noexcept;
};