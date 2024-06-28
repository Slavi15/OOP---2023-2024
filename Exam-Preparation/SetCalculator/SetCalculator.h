#pragma once

#include "StringView.h"

#include "SetExpression.h"

#include "Singleton.h"
#include "UnaryOperation.h"
#include "BinaryOperation.h"

class SetCalculator
{
private:
	SetExpression* expr = nullptr;

	void copyFrom(const SetCalculator& other);
	void moveFrom(SetCalculator&& other) noexcept;
	void free();

	SetExpression* parse(const StringView& view);
	bool isOperation(char ch) const;

public:
	SetCalculator(const String& str);

	SetCalculator(const SetCalculator& other);
	SetCalculator& operator=(const SetCalculator& other);

	SetCalculator(SetCalculator&& other) noexcept;
	SetCalculator& operator=(SetCalculator&& other) noexcept;

	bool isElementIn(const SetExpression::Element& el) const;

	~SetCalculator() noexcept;
};