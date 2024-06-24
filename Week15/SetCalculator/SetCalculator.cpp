#include "SetCalculator.h"

SetCalculator::SetCalculator(const String& str)
{
	this->expr = parse(str);
}

SetCalculator::SetCalculator(const SetCalculator& other)
{
	copyFrom(other);
}

SetCalculator& SetCalculator::operator=(const SetCalculator& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

SetCalculator::SetCalculator(SetCalculator&& other) noexcept
{
	moveFrom(std::move(other));
}

SetCalculator& SetCalculator::operator=(SetCalculator&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

bool SetCalculator::isElementIn(const SetExpression::Element& el) const
{
	return expr->isElementIn(el);
}

SetCalculator::~SetCalculator() noexcept
{
	free();
}

void SetCalculator::copyFrom(const SetCalculator& other)
{
	this->expr = other.expr->clone();
}

void SetCalculator::moveFrom(SetCalculator&& other) noexcept
{
	this->expr = other.expr;
	other.expr = nullptr;
}

void SetCalculator::free()
{
	delete this->expr;
	this->expr = nullptr;
}

SetExpression* SetCalculator::parse(const StringView& view)
{
	if (view.length() == 1)
		return new Singleton(view[0]);

	StringView withoutBrackets = view.substr(1, view.length() - 1);

	size_t count = 0;

	for (size_t i = 0; i < view.length(); i++)
	{
		if (withoutBrackets[i] == '(')
		{
			count++;
		}
		else if (withoutBrackets[i] == ')')
		{
			count--;
		}
		else if (count == 0 && isOperation(withoutBrackets[i]))
		{
			if (withoutBrackets[i] == '!')
			{
				return new UnaryOperation(parse(withoutBrackets.substr(1, view.length() - 1)), '!');
			}
			else
			{
				return new BinaryOperation(parse(withoutBrackets.substr(0, i)), parse(withoutBrackets.substr(i + 1, view.length() - i - 1)), withoutBrackets[i]);
			}
		}
	}
}

bool SetCalculator::isOperation(char ch) const
{
	return ch == '^' || ch == 'v' || ch == '/' || ch == 'x' || ch == '!';
}
