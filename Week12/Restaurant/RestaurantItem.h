#pragma once

#include <iostream>
#include <fstream>

typedef RestaurantItem RI;

enum class ProductType { Empty, Food, Drink };

class RestaurantItem
{
private:
	ProductType type = ProductType::Empty;
	size_t count = 0;
	double price = 0;

public:
	RestaurantItem(ProductType type, size_t count, double price);

	const ProductType getType() const;
	const size_t getCount() const;
	const double getPrice() const;

	void setCount(size_t count);
	void setPrice(double price);
	void setType(ProductType type);

	virtual bool operator>(RestaurantItem* rhs) const = 0; // RestaurantItem == RI as parameter

	virtual void print() const = 0;

	virtual RestaurantItem* clone() const = 0;

	virtual ~RestaurantItem() noexcept = default;
};