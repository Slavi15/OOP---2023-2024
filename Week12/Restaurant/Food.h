#pragma once

#include "RestaurantItem.h"

class Food : public RestaurantItem
{
private:
	ProductType type = ProductType::Food;
	char* name = nullptr;
	double grams = 0;

	void copyFrom(const Food& other);
	void moveFrom(Food&& other) noexcept;
	void free();

public:
	Food(const char* name, double grams, size_t count, double price);

	Food(const Food& other);
	Food& operator=(const Food& other);

	Food(Food&& other) noexcept;
	Food& operator=(Food&& other) noexcept;

	const char* getName() const;
	const double getGrams() const;

	void setName(const char* name);
	void setGrams(double grams);

	bool operator>(RestaurantItem* rhs) const override; // if the param is RI in RestaurantItem, it MUST be here also!!!

	void print() const override;

	RestaurantItem* clone() const override;

	~Food() noexcept;
};