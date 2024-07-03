#include "ExpressionHandler.h"

bool ExpressionHandler::checkAllTruthAssignments(bool value) const
{
	size_t varsCount = myVariables.getTrueCount();
	size_t powerTwo = (1 << varsCount);

	for (size_t i = 0; i < powerTwo; i++)
	{
		BooleanInterPretation current = myVariables;
		current.excludeValuesByMask(i);

		if (expr->eval(current) != value)
			return false;
	}

	return true;
}

bool operator==(const ExpressionHandler& lhs, const ExpressionHandler& rhs)
{
	size_t lhsCount = lhs.myVariables.getTrueCount();
	size_t rhsCount = rhs.myVariables.getTrueCount();

	if (lhsCount != rhsCount) return false;

	size_t powerTwo = (1 << lhsCount);

	for (size_t i = 0; i < powerTwo; i++)
	{
		BooleanInterPretation lhsCurrent = lhs.myVariables;
		BooleanInterPretation rhsCurrent = rhs.myVariables;

		lhsCurrent.excludeValuesByMask(i);
		rhsCurrent.excludeValuesByMask(i);

		if (lhs.expr->eval(lhsCurrent) != rhs.expr->eval(rhsCurrent))
			return false;
	}

	return true;
}

ExpressionHandler::ExpressionHandler(const String& str)
{
	expr = ExpressionFactory::expressionFactory(str);
	expr->populateVariables(myVariables);
}

ExpressionHandler::ExpressionHandler(const ExpressionHandler& other)
{
	copyFrom(other);
}

ExpressionHandler& ExpressionHandler::operator=(const ExpressionHandler& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

ExpressionHandler::ExpressionHandler(ExpressionHandler&& other) noexcept
{
	moveFrom(std::move(other));
}

ExpressionHandler& ExpressionHandler::operator=(ExpressionHandler&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

bool ExpressionHandler::evaluate(const BooleanInterPretation& bi) const
{
	return expr->eval(bi);
}

bool ExpressionHandler::isTautology() const
{
	return checkAllTruthAssignments(true);
}

bool ExpressionHandler::isContradiction() const
{
	return checkAllTruthAssignments(false);
}

ExpressionHandler::~ExpressionHandler() noexcept
{
	free();
}

void ExpressionHandler::copyFrom(const ExpressionHandler& other)
{
	this->expr = other.expr->clone();
}

void ExpressionHandler::moveFrom(ExpressionHandler&& other) noexcept
{
	this->expr = other.expr;
	other.expr = nullptr;
}

void ExpressionHandler::free()
{
	delete this->expr;
}
