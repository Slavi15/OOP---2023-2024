#include "Food.h"

Food::Food(const char* name, double grams, size_t count, double price) : RestaurantItem(ProductType::Food, count, price)
{
	if (!name) return;

	setName(name);
	setGrams(grams);
	setPrice(price);
}

Food::Food(const Food& other) : RestaurantItem(other)
{
	copyFrom(other);
}

Food& Food::operator=(const Food& other)
{
	if (this != &other)
	{
		RestaurantItem::operator=(other);
		free();
		copyFrom(other);
	}

	return *this;
}

Food::Food(Food&& other) noexcept : RestaurantItem(std::move(other))
{
	moveFrom(std::move(other));
}

Food& Food::operator=(Food&& other) noexcept
{
	if (this != &other)
	{
		RestaurantItem::operator=(std::move(other));
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const char* Food::getName() const
{
	return this->name;
}

const double Food::getGrams() const
{
	return this->grams;
}

void Food::setName(const char* name)
{
	if (!name) return;

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Food::setGrams(double grams)
{
	if (grams < 0) return;

	this->grams = grams;
}

bool Food::operator>(RestaurantItem* rhs) const
{
	return getGrams() > dynamic_cast<Food*>(rhs)->getGrams();
}

void Food::print() const
{
	std::cout << getName() << " - " << getGrams() << std::endl;
}

RestaurantItem* Food::clone() const
{
	return new Food(*this);
}

Food::~Food() noexcept
{
	free();
}

void Food::copyFrom(const Food& other)
{
	this->name = new char[strlen(other.name) + 1];
	strcpy(this->name, other.name);

	this->type = other.type;
	this->grams = other.grams;
}

void Food::moveFrom(Food&& other) noexcept
{
	this->name = other.name;
	this->type = other.type;
	this->grams = other.grams;

	other.name = nullptr;
	other.type = ProductType::Empty;
	other.grams = 0;
}

void Food::free()
{
	delete[] this->name;

	this->name = nullptr;
	this->type = ProductType::Empty;
	this->grams = 0;
}
