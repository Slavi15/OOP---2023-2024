#include "Prize.h"

Prize::Prize(double price, size_t points) : points(points)
{
	setPrice(price);
}

const double Prize::getPrice() const
{
	return this->price;
}

const size_t Prize::getPoints() const
{
	return this->points;
}

void Prize::setPrice(double price)
{
	if (price < 0)
		throw std::out_of_range("Price must be positive!");

	this->price = price;
}

void Prize::setPoints(size_t points)
{
	this->points = points;
}

Prize::~Prize() noexcept = default;