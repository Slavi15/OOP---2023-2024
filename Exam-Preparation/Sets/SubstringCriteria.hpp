#pragma once

#include "Vector.hpp"

#define TT template <typename T>

TT
class SubstringCriteria
{
private:
	Vector<T> elements;

public:
	void addElement(const T& element);

	bool operator()(const T& element) const; // !!!! needed because in SetByCriteria we call criteria(element) !!!!

	bool isSubstring(const T& element, const T& pattern) const;
};

TT
void SubstringCriteria<T>::addElement(const T& element)
{
	elements.push_back(element);
}

TT
bool SubstringCriteria<T>::operator()(const T& element) const
{
	for (size_t i = 0; i < elements.getSize(); i++)
	{
		if (isSubstring(elements[i], element))
		{
			return true;
		}
	}

	return false;
}

TT
bool SubstringCriteria<T>::isSubstring(const T& element, const T& pattern) const
{
	size_t elemIndex = 0;
	size_t patternIndex = 0;

	while (true)
	{
		if (!pattern[patternIndex])x
		{
			return true;
		}

		if (!element[elemIndex])
		{
			return false;
		}

		char elemSymbol = element[elemIndex];
		char patternSymbol = element[patternIndex];

		if (elemSymbol == patternSymbol)
		{
			elemIndex++;
			patternIndex++;
		}
		else
		{
			if (element[elemIndex] == pattern[0])
			{
				patternIndex = 0;
			}
			else
			{
				patternIndex = 0;
				elemIndex++;
			}
		}
	}
}
