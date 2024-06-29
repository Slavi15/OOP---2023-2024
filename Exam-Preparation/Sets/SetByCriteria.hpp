#pragma once

#include "Set.hpp"

#define TT template <typename T>

TT
using CriteriaFunc = bool(*)(const T& element);

TT
class SetByCriteria : public Set<T>
{
private:
	CriteriaFunc criteria;

public:
	SetByCriteria(CriteriaFunc criteria);

	bool operator[](const T& element) const override;
	Set* clone() const override;
};

TT
SetByCriteria<T>::SetByCriteria(CriteriaFunc<T> criteria) : criteria(criteria) {}

TT
bool SetByCriteria<T>::operator[](const T& element) const
{
	return criteria(element);
}

TT
inline Set<T>* SetByCriteria<T>::clone() const
{
	return new SetByCriteria(*this);
}
