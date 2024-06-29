#pragma once

#include "Vector.hpp"

#define TT template <typename T>

TT
class ConcatCriteria
{
private:
	Vector<T> elements;

public:
	void addElement(const T& element);

	bool operator()(const T& element) const; // !!!! needed because in SetByCriteria we call criteria(element) !!!!

	bool isConcat(const T& element) const;

	bool concatCompare(const T& element, const T& lhs, const T& rhs) const;
};

TT
void ConcatCriteria<T>::addElement(const T& element)
{
	elements.push_back(element);
}

TT
bool ConcatCriteria<T>::operator()(const T& element) const
{
	return isConcat(element);
}

TT
bool ConcatCriteria<T>::isConcat(const T& element) const
{
	for (size_t i = 0; i < elements.getSize(); i++)
	{
		for (size_t j = 0; j < elements.getSize(); j++)
		{
			if (i != j && concatCompare(element, elements[i], elements[j]))
			{
				return true;
			}
		}
	}

	return false;
}

TT
bool ConcatCriteria<T>::concatCompare(const T& element, const T& lhs, const T& rhs) const
{
	size_t index = 0;
	
	for (size_t i = 0; i < lhs.getSize(); i++)
	{
		if (!element[index])
		{
			return false;
		}

		if (element[index++] != lhs[i])
		{
			return false;
		}
	}

	for (size_t i = 0; i < rhs.getSize(); i++)
	{
		if (!element[index])
		{
			return false;
		}

		if (element[index++] != rhs[i])
		{
			return false;
		}
	}

	if (element[index])
	{
		return false;
	}

	return true;
}
