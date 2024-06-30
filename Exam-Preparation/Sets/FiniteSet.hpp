#pragma once

#include "Set.hpp"
#include "Vector.hpp"

#define TT template <typename T>

TT
class FiniteSet : public Set<T>
{
private:
	Vector<T> data;

public:
	FiniteSet(const Vector<T>& elements);

	bool operator[](const T& element) const override;
	Set<T>* clone() const override;
};

TT
FiniteSet<T>::FiniteSet(const Vector<T>& elements) : data(elements) {}

TT
bool FiniteSet<T>::operator[](const T& element) const
{
	for (size_t i = 0; i < data.getSize(); i++)
	{
		if (data[i] == element)
		{
			return true;
		}
	}

	return false;
}

TT
inline Set<T>* FiniteSet<T>::clone() const
{
	return new FiniteSet(*this);
}
