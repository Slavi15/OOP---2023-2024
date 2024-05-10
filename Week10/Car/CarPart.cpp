#include "CarPart.h"

CarPart::CarPart() = default;

CarPart::CarPart(size_t ID, const char* manufacturer, const char* description)
{
	setID(ID);
	setManufacturer(manufacturer);
	setDescription(description);
}

CarPart::CarPart(const CarPart& other)
{
	copyFrom(other);
}

CarPart& CarPart::operator=(const CarPart& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

CarPart::CarPart(CarPart&& other) noexcept
{
	moveFrom(std::move(other));
}

CarPart& CarPart::operator=(CarPart&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const size_t CarPart::getID() const
{
	return this->ID;
}

const char* CarPart::getManufacturer() const
{
	return this->manufacturer;
}

const char* CarPart::getDescription() const
{
	return this->description;
}

void CarPart::setID(size_t ID)
{
	if (ID < 0)
		throw std::out_of_range("ID must be positive!");

	this->ID = ID;
}

void CarPart::setManufacturer(const char* manufacturer)
{
	if (!manufacturer)
		throw std::runtime_error("NULLPTR!");

	this->manufacturer = new (std::nothrow) char[strlen(manufacturer) + 1];
	strcpy(this->manufacturer, manufacturer);
}

void CarPart::setDescription(const char* description)
{
	if (!description)
		throw std::runtime_error("NULLPTR!");

	this->description = new (std::nothrow) char[strlen(description) + 1];
	strcpy(this->description, description);
}

CarPart::~CarPart() noexcept
{
	free();
}

void CarPart::copyFrom(const CarPart& other)
{
	this->ID = other.ID;

	this->manufacturer = new char[strlen(other.manufacturer) + 1];
	strcpy(this->manufacturer, other.manufacturer);

	this->description = new char[strlen(other.description) + 1];
	strcpy(this->description, other.description);
}

void CarPart::moveFrom(CarPart&& other) noexcept
{
	this->ID = other.ID;
	this->manufacturer = other.manufacturer;
	this->description = other.description;

	other.manufacturer = nullptr;
	other.description = nullptr;
	other.ID = 0;
}

void CarPart::free()
{
	delete[] this->manufacturer;
	delete[] this->description;

	this->manufacturer = nullptr;
	this->description = nullptr;
	this->ID = 0;
}

std::ostream& operator<<(std::ostream& os, const CarPart& carPart)
{
	return os << carPart.getID() << " by " << carPart.getManufacturer() << " - " << carPart.getDescription() << " - ";
}
