#pragma once

#include "BitSet.h"

#include <iostream>
#include <cstdint>
#include <fstream>

#define GRID_DIMENSIONS 20

#define isValidNumber(n) (n >= INT16_MIN && n < INT16_MAX)

class ModifiableIntegersFunction
{
private:
	int16_t(*function)(int16_t number);

	int16_t results[UINT16_MAX]{ 0 };
	bool excludedPoints[UINT16_MAX]{ false };

	mutable bool isModifiedInjection = true;
	mutable bool isModifiedSurjection = true;

	mutable bool isInjectiveFunction = false;
	mutable bool isSurjectiveFunction = false;

	const uint16_t getIndex(int16_t idx) const;

	void readFromFile(std::ifstream& ifs);
	void writeToFile(std::ofstream& ofs) const;

	void calculateResults();

public:
	ModifiableIntegersFunction();
	ModifiableIntegersFunction(int16_t (*func)(int16_t number));

	ModifiableIntegersFunction(const ModifiableIntegersFunction& other);
	ModifiableIntegersFunction& operator=(const ModifiableIntegersFunction& other);

	void setCustomResult(int16_t x, int16_t y);
	void disablePoint(int16_t x);

	ModifiableIntegersFunction& operator+=(const ModifiableIntegersFunction& other);
	ModifiableIntegersFunction& operator-=(const ModifiableIntegersFunction& other);

	ModifiableIntegersFunction& operator()(int16_t(*func)(int16_t number));

	friend ModifiableIntegersFunction operator^(const ModifiableIntegersFunction& other, size_t k);

	friend ModifiableIntegersFunction operator~(const ModifiableIntegersFunction& other);

	friend bool operator<(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
	friend bool operator>(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);

	friend bool operator<=(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
	friend bool operator>=(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);

	friend bool operator==(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
	friend bool operator!=(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);

	friend bool operator||(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);

	friend ModifiableIntegersFunction operator+(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
	friend ModifiableIntegersFunction operator-(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);

	const bool isInjection() const;
	const bool isSurjection() const;
	const bool isBijection() const;

	void readFromFile(const char* fileName);
	void writeToFile(const char* fileName) const;

	void draw(int16_t initialX, int16_t initialY) const;
};