#include "SetByCriteria.h"

void SetByCriteria::extractNumbers()
{
	for (size_t i = 0; i <= getN(); i++)
		add(i);
}

SetByCriteria::SetByCriteria(size_t N, bool(*condition)(size_t n)) : BitSet(N), condition(condition)
{
	extractNumbers();
}

void SetByCriteria::add(size_t n)
{
	if (this->condition(n))
		BitSet::add(n);
	else
		throw std::invalid_argument("Invalid number according to given criteria!");
}

const bool SetByCriteria::contains(size_t n) const
{
	return BitSet::contains(n);
}

void SetByCriteria::remove(size_t n)
{
	if (this->condition(n))
		BitSet::remove(n);
	else
		throw std::invalid_argument("Number does not exist in set!");
}

void SetByCriteria::print() const
{
	BitSet::print();
}

void SetByCriteria::setCondition(bool (*condition)(size_t n))
{
	// Important check, otherwise segmentation fault!!!
	if (condition == NULL)
		throw std::runtime_error("NULL!");

	this->condition = condition;
	BitSet::clear();
	extractNumbers();
}