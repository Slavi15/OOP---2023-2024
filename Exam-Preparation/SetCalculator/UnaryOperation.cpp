#include "UnaryOperation.h"

UnaryOperation::UnaryOperation(SetExpression* expr, char ch) : expr(expr), ch(ch) {}

bool UnaryOperation::isElementIn(const Element& el) const
{
	if (ch == '!')
		return !expr->isElementIn(el);

	return false;
}

SetExpression* UnaryOperation::clone() const
{
	return new UnaryOperation(expr->clone(), ch);
}

UnaryOperation::~UnaryOperation() noexcept
{
	delete expr;
}
