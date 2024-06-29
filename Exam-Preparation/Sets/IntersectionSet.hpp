#pragma once

#include "Set.hpp"
#include "Vector.hpp"

#define TT template <typename T>

TT
class IntersectionSet : public Set<T>
{
private:
	Vector<Set<T>*> sets;

public:
	IntersectionSet(const Vector<Set<T>*>& sets);

	bool operator[](const T& element) const override;
	Set* clone() const override;

	~IntersectionSet() noexcept;
};

TT
IntersectionSet<T>::IntersectionSet(const Vector<Set<T>*>& sets) : sets(sets) {}

TT
bool IntersectionSet<T>::operator[](const T& element) const
{
	for (size_t i = 0; i < sets.getSize(); i++)
	{
		if (!sets[i]->operator[](element))
		{
			return false;
		}
	}

	return true;
}

TT
inline Set<T>* IntersectionSet<T>::clone() const
{
	return new IntersectionSet(*this);
}

TT
inline IntersectionSet<T>::~IntersectionSet() noexcept
{
	for (size_t i = 0; i < sets.getSize(); i++)
		delete sets[i];
}
