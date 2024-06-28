#pragma once

#include "SetExpression.h"

class BinaryOperation : public SetExpression
{
private:
	SetExpression* left = nullptr;
	SetExpression* right = nullptr;
	char ch;

public:
	BinaryOperation(SetExpression* left, SetExpression* right, char ch);

	bool isElementIn(const Element& el) const override;

	SetExpression* clone() const override;

	~BinaryOperation() noexcept;
};