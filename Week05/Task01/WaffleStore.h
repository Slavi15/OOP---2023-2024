#pragma once

#include "Waffle.h"

#define MAX_WAFFLE_COUNT 50

class WaffleStore
{
private:
	Waffle waffles[MAX_WAFFLE_COUNT];
	size_t _currentSize = 0;
	double _income = 0.0;
	double _expenses = 0.0;

	bool setCurrentSize(size_t size);
	bool setIncome(double income);
	bool setExpenses(double expenses);

public:
	WaffleStore();
	
	const size_t getCurrentSize() const;
	const double getIncome() const;
	const double getExpenses() const;

	const int getWaffleByBrand(const char* brand) const;

	void sellWaffle(const char* brand);
	void buyWaffles(const Waffle* waffles, size_t N);

	const size_t getWafflesCount(const char* brand) const;
};