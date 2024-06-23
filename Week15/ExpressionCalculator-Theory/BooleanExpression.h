#pragma once

#include "BooleanInterPretation.h"

class BooleanExpression
{
public:
	BooleanExpression() = default;

	BooleanExpression(const BooleanExpression&) = delete;
	BooleanExpression& operator=(const BooleanExpression&) = delete;

	virtual bool eval(const BooleanInterPretation& interpretation) const = 0;
	virtual void populateVariables(BooleanInterPretation& interpretation) const = 0;

	virtual BooleanExpression* clone() const = 0;
	virtual ~BooleanExpression() noexcept = default;
};