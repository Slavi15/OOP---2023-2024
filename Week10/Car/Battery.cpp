#include "Battery.h"

Battery::Battery() = default;

Battery::Battery(const char* batteryID, size_t batteryCapacity, size_t ID, const char* manufacturer, const char* description) : CarPart(ID, manufacturer, description)
{
	setBatteryID(batteryID);
	setBatteryCapacity(batteryCapacity);
}

Battery::Battery(const Battery& other) : CarPart(other)
{
	copyFrom(other);
}

Battery& Battery::operator=(const Battery& other)
{
	if (this != &other)
	{
		CarPart::operator=(other);
		free();
		copyFrom(other);
	}

	return *this;
}

Battery::Battery(Battery&& other) noexcept : CarPart(std::move(other))
{
	moveFrom(std::move(other));
}

Battery& Battery::operator=(Battery&& other) noexcept
{
	if (this != &other)
	{
		CarPart::operator=(std::move(other));
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const char* Battery::getBatteryID() const
{
	return this->batteryID;
}

const size_t Battery::getBatteryCapacity() const
{
	return this->batteryCapacity;
}

void Battery::setBatteryID(const char* batteryID)
{
	if (!batteryID)
		throw std::runtime_error("NULLPTR!");

	this->batteryID = new (std::nothrow) char[strlen(batteryID) + 1];
	strcpy(this->batteryID, batteryID);
}

void Battery::setBatteryCapacity(size_t batteryCapacity)
{
	if (batteryCapacity < 0)
		throw std::out_of_range("Battery capacity must be positive!");

	this->batteryCapacity = batteryCapacity;
}

Battery::~Battery() noexcept
{
	free();
	// CarPart::~CarPart();
}

void Battery::copyFrom(const Battery& other)
{
	this->batteryID = new char[strlen(other.batteryID) + 1];
	strcpy(this->batteryID, other.batteryID);

	this->batteryCapacity = other.batteryCapacity;
}

void Battery::moveFrom(Battery&& other) noexcept
{
	this->batteryID = other.batteryID;
	this->batteryCapacity = other.batteryCapacity;

	other.batteryID = nullptr;
	other.batteryCapacity = 0;
}

void Battery::free()
{
	delete[] this->batteryID;

	this->batteryID = nullptr;
	this->batteryCapacity = 0;
}

std::ostream& operator<<(std::ostream& os, const Battery& battery)
{
	return os << (CarPart)battery << battery.getBatteryCapacity() << " Ah" << std::endl;
}
