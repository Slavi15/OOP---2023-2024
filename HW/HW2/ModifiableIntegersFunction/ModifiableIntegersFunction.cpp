#include "ModifiableIntegersFunction.h"

ModifiableIntegersFunction::ModifiableIntegersFunction() = default;

ModifiableIntegersFunction::ModifiableIntegersFunction(int16_t(*func)(int16_t number)) : function(func) { calculateResults(); }

ModifiableIntegersFunction::ModifiableIntegersFunction(const ModifiableIntegersFunction& other) = default;

ModifiableIntegersFunction& ModifiableIntegersFunction::operator=(const ModifiableIntegersFunction& other) = default;

const uint16_t ModifiableIntegersFunction::getIndex(int16_t idx) const
{
	return UINT16_MAX / 2 + idx;
}

ModifiableIntegersFunction& ModifiableIntegersFunction::operator+=(const ModifiableIntegersFunction& other)
{
	for (int16_t i = INT16_MIN + 1; i < INT16_MAX; i++)
	{
		int16_t functionResult = results[getIndex(i)] + other.results[getIndex(i)];

		(isValidNumber(functionResult) &&
			!this->excludedPoints[getIndex(results[getIndex(i)])] && 
			!other.excludedPoints[other.getIndex(other.results[other.getIndex(i)])]) ? setCustomResult(i, functionResult) : disablePoint(i);
	}

	return *this;
}

ModifiableIntegersFunction& ModifiableIntegersFunction::operator-=(const ModifiableIntegersFunction& other)
{
	for (int16_t i = INT16_MIN + 1; i < INT16_MAX; i++)
	{
		int16_t functionResult = results[getIndex(i)] - other.results[getIndex(i)];

		(isValidNumber(functionResult) &&
			!this->excludedPoints[getIndex(results[getIndex(i)])] && 
			!other.excludedPoints[other.getIndex(other.results[other.getIndex(i)])]) ? setCustomResult(i, functionResult) : disablePoint(i);
	}

	return *this;
}

ModifiableIntegersFunction& ModifiableIntegersFunction::operator()(int16_t(*func)(int16_t number))
{
	for (int16_t i = INT16_MIN + 1; i < INT16_MAX; i++)
		if (!this->excludedPoints[getIndex(function(i))] && isValidNumber(function(func(i))))
			setCustomResult(i, function(func(i)));

	return *this;
}

ModifiableIntegersFunction operator^(const ModifiableIntegersFunction& other, size_t k)
{
	if (k <= 0)
		throw std::out_of_range("Cannot compose negative number of functions!");

	ModifiableIntegersFunction toReturn(other);

	if (k == 1)
		return toReturn;

	for (size_t i = 1; i < k; i++)
		toReturn.operator()(toReturn.function);

	return toReturn;
}

ModifiableIntegersFunction operator~(const ModifiableIntegersFunction& other)
{
	if (!other.isInjection())
		throw std::invalid_argument("In order to generate an inverse function, it must be injective!");

	ModifiableIntegersFunction toReturn;
	toReturn.function = other.function;

	for (int16_t i = INT16_MIN + 1; i < INT16_MAX; i++)
	{
		int16_t functionResult = toReturn.function(i);
		isValidNumber(functionResult) && !other.excludedPoints[other.getIndex(other.function(i))] ? toReturn.setCustomResult(functionResult, i) : toReturn.disablePoint(functionResult);
	}

	return toReturn;
}

bool operator<(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	for (int16_t i = INT16_MIN + 1; i < INT16_MAX; i++)
	{
		int16_t lhsValue = lhs.results[lhs.getIndex(i)];
		int16_t rhsValue = rhs.results[rhs.getIndex(i)];

		if (lhsValue >= rhsValue || (!lhs.excludedPoints[lhs.getIndex(lhsValue)] && rhs.excludedPoints[rhs.getIndex(rhsValue)]))
			return false;
	}

	return true;
}

bool operator>(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	for (int16_t i = INT16_MIN + 1; i < INT16_MAX; i++)
	{
		int16_t lhsValue = lhs.results[lhs.getIndex(i)];
		int16_t rhsValue = rhs.results[rhs.getIndex(i)];

		if (lhsValue <= rhsValue || (lhs.excludedPoints[lhs.getIndex(lhsValue)] && !rhs.excludedPoints[rhs.getIndex(rhsValue)]))
			return false;
	}

	return true;
}

bool operator<=(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	for (int16_t i = INT16_MIN + 1; i < INT16_MAX; i++)
	{
		int16_t lhsValue = lhs.results[lhs.getIndex(i)];
		int16_t rhsValue = rhs.results[rhs.getIndex(i)];

		if (lhsValue > rhsValue || (!lhs.excludedPoints[lhs.getIndex(lhsValue)] && rhs.excludedPoints[rhs.getIndex(rhsValue)]))
			return false;
	}

	return true;

	//return !(lhs > rhs); // not working with logical operations
}

bool operator>=(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	for (int16_t i = INT16_MIN + 1; i < INT16_MAX; i++)
	{
		int16_t lhsValue = lhs.results[lhs.getIndex(i)];
		int16_t rhsValue = rhs.results[rhs.getIndex(i)];

		if (lhsValue < rhsValue || (lhs.excludedPoints[lhs.getIndex(lhsValue)] && !rhs.excludedPoints[rhs.getIndex(rhsValue)]))
			return false;
	}

	return true;

	//return !(lhs < rhs); // not working with logical operations
}

bool operator==(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	for (int16_t i = INT16_MIN + 1; i < INT16_MAX; i++)
	{
		int16_t lhsValue = lhs.results[lhs.getIndex(i)];
		int16_t rhsValue = rhs.results[rhs.getIndex(i)];

		if (lhsValue != rhsValue || (lhs.excludedPoints[lhs.getIndex(lhsValue)] != rhs.excludedPoints[rhs.getIndex(rhsValue)]))
			return false;
	}

	return true;
}

bool operator!=(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	return !(lhs == rhs);
}

bool operator||(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	for (int16_t i = INT16_MIN + 1; i < INT16_MAX; i++)
	{
		if (isValidNumber(lhs.function(i)) && isValidNumber(rhs.function(i)))
		{
			int16_t lhsChange = lhs.function(i + 1) - lhs.function(i);
			int16_t rhsChange = rhs.function(i + 1) - rhs.function(i);

			if (lhsChange != rhsChange)
				return false;
		}
	}

	return true;
}

ModifiableIntegersFunction operator+(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	ModifiableIntegersFunction toReturn(lhs);
	toReturn += rhs;
	return toReturn;
}

ModifiableIntegersFunction operator-(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	ModifiableIntegersFunction toReturn(lhs);
	toReturn -= rhs;
	return toReturn;
}

const bool ModifiableIntegersFunction::isInjection() const
{
	if (!isModifiedInjection)
		return isInjectiveFunction;

	isModifiedInjection = false;

	BitSet injection(UINT16_MAX);

	for (int16_t i = INT16_MIN + 1; i < INT16_MAX; i++)
	{
		int16_t result = this->results[getIndex(i)];

		if (!this->excludedPoints[getIndex(result)])
		{
			if (injection.contains(getIndex(result)))
			{
				isInjectiveFunction = false;
				return isInjectiveFunction;
			}

			injection.add(getIndex(result));
		}
	}

	isInjectiveFunction = true;
	return isInjectiveFunction;
}

const bool ModifiableIntegersFunction::isSurjection() const
{
	if (!isModifiedSurjection)
		return isSurjectiveFunction;

	isModifiedSurjection = false;

	BitSet surjection(UINT16_MAX);

	for (int16_t i = INT16_MIN + 1; i < INT16_MAX; i++)
	{
		int16_t result = this->results[getIndex(i)];

		if (!surjection.contains(getIndex(result)) && !this->excludedPoints[getIndex(result)])
			surjection.add(getIndex(result));
	}

	(surjection.getNumbersCount() == UINT16_MAX - 1) ? isSurjectiveFunction = true : isSurjectiveFunction = false;
	return isSurjectiveFunction;
}

const bool ModifiableIntegersFunction::isBijection() const
{
	return isInjection() && isSurjection();
}

void ModifiableIntegersFunction::readFromFile(std::ifstream& ifs)
{
	ifs.read((char*)&this->function, sizeof(this->function));
	ifs.read((char*)this->results, sizeof(int16_t) * UINT16_MAX);
	ifs.read((char*)this->excludedPoints, sizeof(bool) * UINT16_MAX);
}

void ModifiableIntegersFunction::writeToFile(std::ofstream& ofs) const
{
	ofs.write((const char*)&this->function, sizeof(this->function));
	ofs.write((const char*)this->results, sizeof(int16_t) * UINT16_MAX);
	ofs.write((const char*)this->excludedPoints, sizeof(bool) * UINT16_MAX);
}

void ModifiableIntegersFunction::readFromFile(const char* fileName)
{
	if (!fileName)
		throw std::runtime_error("NULLPTR!");

	std::ifstream ifs(fileName, std::ios::in | std::ios::binary);
	if (!ifs.is_open())
		throw std::runtime_error("File cannot be opened!");

	return readFromFile(ifs);
}

void ModifiableIntegersFunction::writeToFile(const char* fileName) const
{
	if (!fileName)
		throw std::runtime_error("NULLPTR!");

	std::ofstream ofs(fileName, std::ios::out | std::ios::binary);
	if (!ofs.is_open())
		throw std::runtime_error("File cannot be opened!");

	return writeToFile(ofs);
}

void ModifiableIntegersFunction::draw(int16_t initialX, int16_t initialY) const
{
	int16_t startX = initialX - (GRID_DIMENSIONS / 2);
	int16_t startY = initialY - (GRID_DIMENSIONS / 2);

	int16_t endX = initialX + (GRID_DIMENSIONS / 2);
	int16_t endY = initialY + (GRID_DIMENSIONS / 2);

	for (int16_t y = endY; y >= startY; y--)
	{
		for (int16_t x = startX; x <= endX; x++)
		{
			int16_t result = this->results[getIndex(x)];

			if (result == y && !this->excludedPoints[getIndex(result)])
				std::cout << "* ";
			else if (y == 0)
				std::cout << "- ";
			else if (x == 0)
				std::cout << "| ";
			else
				std::cout << "  ";
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
}

void ModifiableIntegersFunction::setCustomResult(int16_t x, int16_t y)
{
	uint16_t resultsIndex = getIndex(x);

	isModifiedInjection = true;
	isModifiedSurjection = true;

	this->results[resultsIndex] = y;
	this->excludedPoints[getIndex(y)] = false;
}

void ModifiableIntegersFunction::disablePoint(int16_t x)
{
	uint16_t occurencesIndex = getIndex(results[getIndex(x)]);

	isModifiedInjection = true;
	isModifiedSurjection = true;

	this->excludedPoints[occurencesIndex] = true;
}

void ModifiableIntegersFunction::calculateResults()
{
	for (int16_t i = INT16_MIN; i < INT16_MAX; i++)
	{
		int16_t functionResult = function(i);
		isValidNumber(functionResult) ? setCustomResult(i, functionResult) : disablePoint(i);
	}
}