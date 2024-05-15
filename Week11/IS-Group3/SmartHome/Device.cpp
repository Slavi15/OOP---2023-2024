#include "Device.h"

Device::Device() = default;

Device::Device(const char* name, const char* manufacturer)
{
	setName(name);
	setManufacturer(manufacturer);
}

Device::Device(const Device& other)
{
	copyFrom(other);
}

Device& Device::operator=(const Device& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Device::Device(Device&& other) noexcept
{
	moveFrom(std::move(other));
}

Device& Device::operator=(Device&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

void Device::printDetails() const
{
	std::cout << "Name: " << getName() << std::endl;
	std::cout << "Manufacturer: " << getManufacturer() << std::endl;
}

const char* Device::getName() const
{
	return this->name;
}

const char* Device::getManufacturer() const
{
	return this->manufacturer;
}

void Device::setName(const char* name)
{
	if (!name) return;

	delete[] this->name;

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Device::setManufacturer(const char* manufacturer)
{
	if (!manufacturer) return;

	delete[] this->manufacturer;

	this->manufacturer = new char[strlen(manufacturer) + 1];
	strcpy(this->manufacturer, manufacturer);
}

Device::~Device() noexcept
{
	free();
}

void Device::copyFrom(const Device& other)
{
	this->name = new char[strlen(other.name) + 1];
	strcpy(this->name, other.name);

	this->manufacturer = new char[strlen(other.manufacturer) + 1];
	strcpy(this->manufacturer, other.manufacturer);
}

void Device::moveFrom(Device&& other) noexcept
{
	this->name = other.name;
	this->manufacturer = other.manufacturer;

	other.name = nullptr;
	other.manufacturer = nullptr;
}

void Device::free()
{
	delete[] this->name;
	delete[] this->manufacturer;

	this->name = nullptr;
	this->manufacturer = nullptr;
}
