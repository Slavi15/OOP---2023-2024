#pragma once

#include "Set.hpp"
#include "Vector.hpp"

#define TT template <typename T>

TT
class UnionSet : public Set<T>
{
private:
	Vector<Set<T>*> sets;

public:
	UnionSet(const Vector<Set<T>*>& sets);

	bool operator[](const T& element) const override;
	Set* clone() const override;

	~UnionSet() noexcept;
};

TT
UnionSet<T>::UnionSet(const Vector<Set<T>*>& sets) : sets(sets) {}

TT
bool UnionSet<T>::operator[](const T& element) const
{
	for (size_t i = 0; i < sets.getSize(); i++)
	{
		if (sets[i]->operator[](element))
		{
			return true;
		}
	}

	return false;
}

TT
inline Set<T>* UnionSet<T>::clone() const
{
	return new UnionSet(*this);
}

TT
inline UnionSet<T>::~UnionSet() noexcept
{
	for (size_t i = 0; i < sets.getSize(); i++)
		delete sets[i];
}
