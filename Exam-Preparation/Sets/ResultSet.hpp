#pragma once

#include "Set.hpp"
#include "Vector.hpp"

#include "UnionSet.hpp"
#include "IntersectionSet.hpp"

#define TT template <typename T>

TT
class ResultSet
{
private:
	Set<T>* resultSet = nullptr;

	void addByUnion(Set<T>* set);
	void addByIntersection(Set<T>* set);

public:
	ResultSet();

	void addSet(Set<T>* set, uint8_t addType);
};

TT
ResultSet<T>::ResultSet() = default;

TT
inline void ResultSet<T>::addByUnion(Set<T>* set)
{
	Vector<Set<T>*> newSets;

	newSets.push_back(resultSet);
	newSets.push_back(set);

	Set<T>* unionSet = new UnionSet<T>(newSets);
	resultSet = unionSet;
}

TT
inline void ResultSet<T>::addByIntersection(Set<T>* set)
{
	Vector<Set<T>*> newSets;

	newSets.push_back(resultSet);
	newSets.push_back(set);

	Set<T>* intersectionSet = new IntersectionSet<T>(newSets);
	resultSet = intersectionSet;
}

TT
void ResultSet<T>::addSet(Set<T>* set, uint8_t addType)
{
	if (!resultSet)
	{
		resultSet = set;
		return;
	}

	switch (addType)
	{
	case 0:
	{
		delete resultSet;
		resultSet = set;
		break;
	}
	case 1:
		addByUnion(set);
		break;
	case 2:
		addByIntersection(set);
		break;
	}
}