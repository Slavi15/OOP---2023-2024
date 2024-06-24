#pragma once

#include "SetExpression.h"

class UnaryOperation : public SetExpression
{
private:
	SetExpression* expr = nullptr;
	char ch;

public:
	UnaryOperation(SetExpression* expr, char ch);

	bool isElementIn(const Element& el) const override;

	SetExpression* clone() const override;

	~UnaryOperation() noexcept;
};