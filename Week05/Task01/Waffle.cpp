#include "Waffle.h"

Waffle::Waffle() = default;

Waffle::Waffle(const char* brand, size_t calories, double factoryPrice, double clientPrice) : _calories(calories), _factoryPrice(factoryPrice), _clientPrice(clientPrice)
{
	setBrand(brand);
}

const char* Waffle::getBrand() const
{
	return _brand;
}

const size_t Waffle::getCalories() const
{
	return _calories;
}

const double Waffle::getFactoryPrice() const
{
	return _factoryPrice;
}

const double Waffle::getClientPrice() const
{
	return _clientPrice;
}

bool Waffle::setBrand(const char* brand)
{
	if (!brand) return false;

	if (strlen(brand) <= MAX_BRAND_LENGTH)
		strcpy(_brand, brand);

	return true;
}

bool Waffle::setCalories(size_t calories)
{
	if (calories <= 0) return false;

	_calories = calories;
	return true;
}

bool Waffle::setFactoryPrice(double factoryPrice)
{
	if (factoryPrice <= 0) return false;

	_factoryPrice = factoryPrice;
	return true;
}

bool Waffle::setClientPrice(double clientPrice)
{
	if (clientPrice <= 0) return false;

	_clientPrice = clientPrice;
	return true;
}
