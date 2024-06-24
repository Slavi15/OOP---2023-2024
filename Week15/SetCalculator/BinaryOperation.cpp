#include "BinaryOperation.h"

BinaryOperation::BinaryOperation(SetExpression* left, SetExpression* right, char ch) : left(left), right(right), ch(ch) {}

bool BinaryOperation::isElementIn(const Element& el) const
{
	switch (ch)
	{
	case '^':
		return left->isElementIn(el) && right->isElementIn(el);
	case 'v':
		return left->isElementIn(el) || right->isElementIn(el);
	case '/':
		return left->isElementIn(el) && !right->isElementIn(el);
	case 'x':
		return (left->isElementIn(el) && !right->isElementIn(el)) || (!left->isElementIn(el) && right->isElementIn(el));
	}

	return false;
}

SetExpression* BinaryOperation::clone() const
{
	return new BinaryOperation(left->clone(), right->clone(), ch);
}

BinaryOperation::~BinaryOperation() noexcept
{
	delete left;
	delete right;
}
