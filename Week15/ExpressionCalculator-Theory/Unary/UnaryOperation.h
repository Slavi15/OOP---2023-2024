#pragma once

#include "../BooleanExpression.h"

class UnaryOperation : public BooleanExpression
{
protected:
	BooleanExpression* expr = nullptr;

public:
	UnaryOperation(BooleanExpression* expr);

	void populateVariables(BooleanInterPretation& interpretation) const override;

	~UnaryOperation() noexcept;
};