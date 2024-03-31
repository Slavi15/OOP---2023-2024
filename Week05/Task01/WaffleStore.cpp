#include "WaffleStore.h"

WaffleStore::WaffleStore() = default;

const size_t WaffleStore::getCurrentSize() const
{
	return _currentSize;
}

const double WaffleStore::getIncome() const
{
	return _income;
}

const double WaffleStore::getExpenses() const
{
	return _expenses;
}

bool WaffleStore::setCurrentSize(size_t size)
{
	if (size <= 0) return false;

	_currentSize = size;
	return true;
}

bool WaffleStore::setIncome(double income)
{
	if (income <= 0) return false;

	_income = income;
	return true;
}

bool WaffleStore::setExpenses(double expenses)
{
	if (expenses <= 0) return false;

	_expenses = expenses;
	return true;
}

const int WaffleStore::getWaffleByBrand(const char* brand) const
{
	if (!brand) return -1;

	for (size_t i = 0; i < _currentSize; i++)
		if (strcmp(waffles[i].getBrand(), brand) == 0)
			return i;

	return -1;
}

void WaffleStore::sellWaffle(const char* brand)
{
	if (!brand) return;

	int index = getWaffleByBrand(brand);
	if (index == -1) return;

	waffles[index] = waffles[_currentSize - 1];
	_currentSize--;
}

void WaffleStore::buyWaffles(const Waffle* waffles, size_t N)
{
	if (!waffles) return;

	for (size_t i = 0; i < N; i++)
		if (_currentSize < MAX_WAFFLE_COUNT)
			this->waffles[_currentSize++] = waffles[i];
}

const size_t WaffleStore::getWafflesCount(const char* brand) const
{
	if (!brand) return 0;

	size_t result = 0;

	for (size_t i = 0; i < _currentSize; i++)
		if (strcmp(waffles[i].getBrand(), brand) == 0)
			result++;

	return result;
}
