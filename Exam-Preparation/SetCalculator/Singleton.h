#pragma once

#include "SetExpression.h"

class Singleton : public SetExpression
{
private:
	char ch;

public:
	Singleton(char ch);

	bool isElementIn(const Element& el) const override;

	SetExpression* clone() const override;
};