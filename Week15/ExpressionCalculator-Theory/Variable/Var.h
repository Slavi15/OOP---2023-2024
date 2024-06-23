#pragma once

#include "../BooleanExpression.h"

class Var : public BooleanExpression
{
private:
	char ch;

public:
	Var(char ch);

	bool eval(const BooleanInterPretation& interpretation) const override;

	void populateVariables(BooleanInterPretation& interpretation) const override;

	BooleanExpression* clone() const override;
};