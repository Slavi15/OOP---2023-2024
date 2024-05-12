#pragma once

#include "BitSet.h"

class SetByCriteria : private BitSet
{
private:
	bool (*condition)(size_t n);

	void extractNumbers();

public:
	SetByCriteria(size_t N, bool (*condition)(size_t n));

	void add(size_t n);

	const bool contains(size_t n) const;

	void remove(size_t n);

	void print() const;

	void setCondition(bool (*condition)(size_t n));
};