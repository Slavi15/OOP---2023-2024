#pragma once

#include <iostream>
#include <fstream>

#include "Set.hpp"
#include "Vector.hpp"

#include "FiniteSet.hpp"
#include "IntervalSet.hpp"
#include "SetByCriteria.hpp" // it wraps one of the criterias down below
#include "SubstringCriteria.hpp"
#include "ConcatCriteria.hpp"
#include "UnionSet.hpp"
#include "IntersectionSet.hpp"

#define TT template <typename T>

TT
class SetFactory
{
private:
	Set<T>* readFiniteSet(std::ifstream& ifs, uint32_t elementCount);
	Set<T>* readIntervalSet(std::ifstream& ifs, uint32_t elementCount);
	Set<T>* readSubstringSet(std::ifstream& ifs, uint32_t elementCount);
	Set<T>* readConcatSet(std::ifstream& ifs, uint32_t elementCount);
	Set<T>* readUnionSet(std::ifstream& ifs, uint32_t elementCount);
	Set<T>* readIntersectionSet(std::ifstream& ifs, uint32_t elementCount);

	Set<T>* readSet(std::ifstream& ifs, uint32_t elementCount, uint8_t addType);

public:
	Set<T>* readFromFile(const char* fileName);
};

TT
Set<T>* readFromFile(const char* fileName)
{
	if (!fileName) return nullptr;

	std::ifstream ifs(fileName, std::ios::in | std::ios::binary);

	if (!ifs.is_open()) return nullptr;

	uint32_t elemCount = 0;
	uint8_t addType = 0;

	ifs.read(reinterpret_cast<char*>(&elemCount), sizeof(uint32_t));
	ifs.read(reinterpret_cast<char*>(&addType), sizeof(uint8_t));

	uint8_t setType  = (addType >> 5); // according to the task, this is how we obtain setType

	return readSet(ifs, elemCount, setType);
}

TT
Set<T>* readSet(std::ifstream& ifs, uint32_t elementCount, uint8_t addType)
{
	switch (addType)
	{
	case 0: return readFiniteSet(ifs, addType);
	case 1: return readIntervalSet(ifs, addType);
	case 2: return readSubstringSet(ifs, addType);
	case 3: return readConcatSet(ifs, addType);
	case 4: return readUnionSet(ifs, addType);
	case 5: return readIntersectionSet(ifs, addType);
	}
}

TT
Set<T>* readFiniteSet(std::ifstream& ifs, uint32_t elementCount)
{
	Vector<T> toReturn;

	for (size_t i = 0; i < elementCount; i++)
	{
		size_t strLength = 0;
		ifs.read(reinterpret_cast<char*>(&strLength), sizeof(size_t));

		char* string = new char[strLength + 1] {};
		string[strLength] = '\0';
		ifs.read(reinterpret_cast<char*>(string), sizeof(char) * strLength);

		toReturn.push_back(string);

		delete[] string;
	}

	return new FiniteSet<T>(toReturn);
}

TT
Set<T>* readIntervalSet(std::ifstream& ifs, uint32_t elementCount)
{
	if (elementCount > 2) return nullptr;

	size_t leftLength = 0;
	ifs.read(reinterpret_cast<char*>(&leftLength), sizeof(size_t));

	char* leftBound = new char[leftLength + 1] {};
	leftBound[leftLength] = '\0';
	ifs.read(reinterpret_cast<char*>(leftBound), leftLength * sizeof(char));

	size_t rightLength = 0;
	ifs.read(reinterpret_cast<char*>(&rightLength), sizeof(size_t));

	char* rightBound = new char[rightLength + 1] {};
	rightBound[rightLength] = '\0';
	ifs.read(reinterpret_cast<char*>(rightBound), rightLength * sizeof(char));

	T leftInterval(leftBound);
	T rightInterval(rightBound);

	delete[] leftBound;
	delete[] rightBound;

	return new IntervalSet<T>(leftInterval, rightInterval);
}

TT
Set<T>* readSubstringSet(std::ifstream& ifs, uint32_t elementCount)
{
	SubstringCriteria<T> criteria;

	for (size_t i = 0; i < elementCount; i++)
	{
		size_t strLength = 0;
		ifs.read(reinterpret_cast<char*>(&strLength), sizeof(size_t));

		char* substring = new char[strLength + 1] {};
		substring[strLength] = '\0';
		ifs.read(reinterpret_cast<char*>(substring), strLength * sizeof(char));

		criteria.addElement(substring);

		delete[] substring;
	}

	return new SetByCriteria<T>(criteria);
}

TT
Set<T>* readConcatSet(std::ifstream& ifs, uint32_t elementCount)
{
	ConcatCriteria<T> criteria;

	for (size_t i = 0; i < elementCount; i++)
	{
		size_t strLength = 0;
		ifs.read(reinterpret_cast<char*>(&strLength), sizeof(size_t));

		char* string = new char[strLength + 1] {};
		string[strLength] = '\0';
		ifs.read(reinterpret_cast<char*>(string), strLength * sizeof(char));

		criteria.addElement(string);

		delete[] string;
	}

	return new SetByCriteria<T>(criteria);
}

TT
Set<T>* readUnionSet(std::ifstream& ifs, uint32_t elementCount)
{
	if (elementCount % 2 != 0) return nullptr;

	Vector<Set<T>*> intervalSets;

	size_t loopBoundary = elementCount / 2;
	for (size_t i = 0; i < loopBoundary; i++)
	{
		Set<T>* intervalSet = readIntervalSet(ifs, 2);
		intervalSets.push_back(intervalSet);
	}

	return new UnionSet<T>(intervalSets);
}

TT
Set<T>* readIntersectionSet(std::ifstream& ifs, uint32_t elementCount)
{
	if (elementCount % 2 != 0) return nullptr;

	Vector<Set<T>*> intervalSets;

	size_t loopBoundary = elementCount / 2;
	for (size_t i = 0; i < loopBoundary; i++)
	{
		Set<T>* intervalSet = readIntervalSet(ifs, 2);
		intervalSets.push_back(intervalSet);
	}

	return new IntersectionSet<T>(intervalSets);
}
