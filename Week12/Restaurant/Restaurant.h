#pragma once

#include "RestaurantItem.h"

class Restaurant
{
private:
	RestaurantItem** container = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	Restaurant(size_t newSize);
	void resize(size_t newCapacity);

	const unsigned int getNextPowerOfTwo(unsigned int n) const;
	const unsigned int allocateCapacity(unsigned int size) const;

	void copyFrom(const Restaurant& other);
	void moveFrom(Restaurant&& other) noexcept;
	void free();

	void addItem(RestaurantItem* item);

public:
	Restaurant();

	Restaurant(const Restaurant& other);
	Restaurant& operator=(const Restaurant& other);

	Restaurant(Restaurant&& other) noexcept;
	Restaurant& operator=(Restaurant&& other) noexcept;

	const size_t getSize() const;
	const size_t getCapacity() const;

	void addFood(const char* name, double grams, size_t count, double price);
	void addDrink(const char* name, size_t alcohol, size_t count, double price);

	void remove(size_t index);

	void changePrice(size_t index, double newPrice);
	void changeName(size_t index, const char* newName);

	void printRestaurant() const;
	void printNonAlcoholDrinks() const;

	~Restaurant() noexcept;
};