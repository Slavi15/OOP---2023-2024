#pragma once

#include <iostream>
#include <fstream>

class Prize
{
private:
	double price = 0;
	size_t points = 0;

public:
	Prize(double price, size_t points);

	virtual const char* visualize() const = 0;

	const double getPrice() const;
	const size_t getPoints() const;

	void setPrice(double price);
	void setPoints(size_t points);

	virtual ~Prize() noexcept;
};