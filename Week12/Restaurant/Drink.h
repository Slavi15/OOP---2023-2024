#pragma once

#include "RestaurantItem.h"

class Drink : public RestaurantItem
{
private:
	ProductType type = ProductType::Drink;
	char* name = nullptr;
	size_t alcohol = 0;

	void copyFrom(const Drink& other);
	void moveFrom(Drink&& other) noexcept;
	void free();

public:
	Drink(const char* name, size_t alcohol, size_t count, double price);

	Drink(const Drink& other);
	Drink& operator=(const Drink& other);

	Drink(Drink&& other) noexcept;
	Drink& operator=(Drink&& other) noexcept;

	const char* getName() const;
	const double getAlcohol() const;

	void setName(const char* name);
	void setAlcohol(size_t alcohol);

	bool operator>(RestaurantItem* rhs) const override; // if the param is RI in RestaurantItem, it MUST be here also!!!

	void print() const override;

	RestaurantItem* clone() const override;

	~Drink() noexcept;
};