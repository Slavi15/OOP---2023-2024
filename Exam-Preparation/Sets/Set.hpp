#pragma once

#include <iostream>

#define TT template <typename T>

TT
class Set
{
public:
	virtual bool operator[](const T& element) const = 0;
	virtual Set* clone() const = 0;

	virtual ~Set() noexcept = default;
};