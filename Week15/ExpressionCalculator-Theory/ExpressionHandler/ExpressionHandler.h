#pragma once

#include "../String and StringView/String.h"

#include "../BooleanExpression.h"
#include "../BooleanInterPretation.h"

#include "../Factory/ExpressionFactory.h"

class ExpressionHandler
{
private:
	BooleanExpression* expr = nullptr;
	BooleanInterPretation myVariables;

	void copyFrom(const ExpressionHandler& other);
	void moveFrom(ExpressionHandler&& other) noexcept;
	void free();

	bool checkAllTruthAssignments(bool value) const;

public:
	ExpressionHandler(const String& str);

	ExpressionHandler(const ExpressionHandler& other);
	ExpressionHandler& operator=(const ExpressionHandler& other);

	ExpressionHandler(ExpressionHandler&& other) noexcept;
	ExpressionHandler& operator=(ExpressionHandler&& other) noexcept;

	bool evaluate(const BooleanInterPretation& bi) const;

	bool isTautology() const;
	bool isContradiction() const;

	friend bool operator==(const ExpressionHandler& lhs, const ExpressionHandler& rhs);

	~ExpressionHandler() noexcept;
};