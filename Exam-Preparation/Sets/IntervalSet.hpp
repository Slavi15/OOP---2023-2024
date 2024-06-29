#pragma once

#include "Set.hpp"

#define TT template <typename T>

TT
class IntervalSet : public Set<T>
{
private:
	T left;
	T right;

public:
	IntervalSet(const T& left, const T& right);

	bool operator[](const T& element) const override;
	Set* clone() const override;
};

TT
IntervalSet<T>::IntervalSet(const T& left, const T& right) : left(std::min(left, right)), right(std::max(left, right)) {}

TT
bool IntervalSet<T>::operator[](const T& element) const
{
	return element >= left && element <= right;
}

TT
inline Set<T>* IntervalSet<T>::clone() const
{
	return new IntervalSet(*this);
}
