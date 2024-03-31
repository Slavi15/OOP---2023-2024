#pragma once

#include <iostream>

#define MAX_BRAND_LENGTH 20

class Waffle
{
private:
	char _brand[MAX_BRAND_LENGTH + 1] = "";
	size_t _calories = 0;
	double _factoryPrice = 0.0;
	double _clientPrice = 0.0;

public:
	Waffle();
	Waffle(const char* brand, size_t calories, double factoryPrice, double clientPrice);

	const char* getBrand() const;
	const size_t getCalories() const;
	const double getFactoryPrice() const;
	const double getClientPrice() const;

	bool setBrand(const char* brand);
	bool setCalories(size_t calories);
	bool setFactoryPrice(double factoryPrice);
	bool setClientPrice(double clientPrice);
};