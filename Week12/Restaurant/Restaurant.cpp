#include "Restaurant.h"

#include "Food.h"
#include "Drink.h"

Restaurant::Restaurant() : Restaurant(4) {}

Restaurant::Restaurant(size_t newSize) : size(0)
{
	this->capacity = allocateCapacity(newSize);
	this->container = new RestaurantItem * [this->capacity];
}

Restaurant::Restaurant(const Restaurant& other)
{
	copyFrom(other);
}

Restaurant& Restaurant::operator=(const Restaurant& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Restaurant::Restaurant(Restaurant&& other) noexcept
{
	moveFrom(std::move(other));
}

Restaurant& Restaurant::operator=(Restaurant&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const size_t Restaurant::getSize() const
{
	return this->size;
}

const size_t Restaurant::getCapacity() const
{
	return this->capacity;
}

void Restaurant::addItem(RestaurantItem* item)
{
	if (getSize() >= getCapacity())
		resize(getCapacity() * 2);

	this->container[this->size++] = item;
}

void Restaurant::addFood(const char* name, double grams, size_t count, double price)
{
	if (!name) return;

	Food* newFood = new Food(name, grams, count, price);
	addItem(newFood);
}

void Restaurant::addDrink(const char* name, size_t alcohol, size_t count, double price)
{
	if (!name) return;

	Drink* newDrink = new Drink(name, alcohol, count, price);
	addItem(newDrink);
}

void Restaurant::remove(size_t index)
{
	if (index >= getSize()) return;

	if (getSize())
		this->size--;
	else
		return;

	std::swap(this->container[index], this->container[getSize()]);

	if (getSize() * 4 <= getCapacity() && getCapacity() > 1)
		resize(getCapacity() / 2);
}

void Restaurant::changePrice(size_t index, double newPrice)
{
	if (index >= getSize()) return;

	this->container[index]->setPrice(newPrice);
}

void Restaurant::changeName(size_t index, const char* newName)
{
	if (!newName) return;
	if (index >= getSize()) return;

	if (this->container[index]->getType() == ProductType::Food)
		dynamic_cast<Food*>(this->container[index])->setName(newName);
	else if (this->container[index]->getType() == ProductType::Drink)
		dynamic_cast<Drink*>(this->container[index])->setName(newName);
}

void Restaurant::printRestaurant() const
{
	for (size_t i = 0; i < getSize(); i++)
		this->container[i]->print();
}

void Restaurant::printNonAlcoholDrinks() const
{
	for (size_t i = 0; i < getSize(); i++)
		if (this->container[i]->getType() == ProductType::Drink && dynamic_cast<Drink*>(this->container[i])->getAlcohol() == 0)
			this->container[i]->print();
}

Restaurant::~Restaurant() noexcept
{
	free();
}

void Restaurant::resize(size_t newCapacity)
{
	RestaurantItem** newContainer = new RestaurantItem * [newCapacity];
	for (size_t i = 0; i < getSize(); i++)
		newContainer[i] = this->container[i];

	delete[] this->container;
	this->container = newContainer;
	this->capacity = newCapacity;
}

const unsigned int Restaurant::getNextPowerOfTwo(unsigned int n) const
{
	if (n == 0) return 1;

	while (n & (n - 1))
		n &= (n - 1);

	return n << 1;
}

const unsigned int Restaurant::allocateCapacity(unsigned int size) const
{
	return std::max(allocateCapacity(size + 1), 8u);
}

void Restaurant::copyFrom(const Restaurant& other)
{
	this->size = other.size;
	this->capacity = other.capacity;

	this->container = new RestaurantItem * [this->capacity];
	for (size_t i = 0; i < this->capacity; i++)
		this->container[i] = other.container[i]->clone();
}

void Restaurant::moveFrom(Restaurant&& other) noexcept
{
	this->container = other.container;
	this->size = other.size;
	this->capacity = other.capacity;

	other.container = nullptr;
	other.size = other.capacity = 0;
}

void Restaurant::free()
{
	for (size_t i = 0; i < this->size; i++)
		delete this->container[i];

	delete[] this->container;
	this->container = nullptr;
	this->size = this->capacity = 0;
}
