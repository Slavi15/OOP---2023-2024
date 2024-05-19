#include "Drink.h"

Drink::Drink(const char* name, size_t alcohol, size_t count, double price) : RestaurantItem(ProductType::Drink, count, price)
{
	if (!name) return;

	setName(name);
	setAlcohol(alcohol);
	setPrice(price);
}

Drink::Drink(const Drink& other) : RestaurantItem(other)
{
	copyFrom(other);
}

Drink& Drink::operator=(const Drink& other)
{
	if (this != &other)
	{
		RestaurantItem::operator=(other);
		free();
		copyFrom(other);
	}

	return *this;
}

Drink::Drink(Drink&& other) noexcept : RestaurantItem(std::move(other))
{
	moveFrom(std::move(other));
}

Drink& Drink::operator=(Drink&& other) noexcept
{
	if (this != &other)
	{
		RestaurantItem::operator=(std::move(other));
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const char* Drink::getName() const
{
	return this->name;
}

const double Drink::getAlcohol() const
{
	return this->alcohol;
}

void Drink::setName(const char* name)
{
	if (!name) return;

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Drink::setAlcohol(size_t alcohol)
{
	if (alcohol < 0) return;

	this->alcohol = alcohol;
}

bool Drink::operator>(RestaurantItem* rhs) const
{
	return getAlcohol() > dynamic_cast<Drink*>(rhs)->getAlcohol();
}

void Drink::print() const
{
	std::cout << getName() << " - " << getAlcohol() << std::endl;
}

RestaurantItem* Drink::clone() const
{
	return new Drink(*this);
}

Drink::~Drink() noexcept
{
	free();
}

void Drink::copyFrom(const Drink& other)
{
	this->name = new char[strlen(other.name) + 1];
	strcpy(this->name, other.name);

	this->type = other.type;
	this->alcohol = other.alcohol;
}

void Drink::moveFrom(Drink&& other) noexcept
{
	this->name = other.name;
	this->type = other.type;
	this->alcohol = other.alcohol;

	other.name = nullptr;
	other.type = ProductType::Empty;
	other.alcohol = 0;
}

void Drink::free()
{
	delete[] this->name;

	this->name = nullptr;
	this->type = ProductType::Empty;
	this->alcohol = 0;
}