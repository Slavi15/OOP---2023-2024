#pragma once

#include <iostream>
#include <cassert>

#define BOOLEAN_ARRAY_LENGTH 26

class BooleanInterPretation
{
private:
	bool values[BOOLEAN_ARRAY_LENGTH]{ false };

public:
	void set(char ch, bool value);

	bool operator()(char ch) const;

	size_t getTrueCount() const;

	void excludeValuesByMask(size_t mask);
};