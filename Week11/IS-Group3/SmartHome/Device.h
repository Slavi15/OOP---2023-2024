#pragma once

#include <iostream>

class Device
{
private:
	char* name = nullptr;
	char* manufacturer = nullptr;

	void copyFrom(const Device& other);
	void moveFrom(Device&& other) noexcept;
	void free();

public:
	virtual void turnOn() const = 0;
	virtual void turnOff() const = 0;
	virtual void printDetails() const;

	Device();
	Device(const char* name, const char* manufacturer);

	Device(const Device& other);
	Device& operator=(const Device& other);

	Device(Device&& other) noexcept;
	Device& operator=(Device&& other) noexcept;

	const char* getName() const;
	const char* getManufacturer() const;

	void setName(const char* name);
	void setManufacturer(const char* manufacturer);

	virtual ~Device() noexcept;
};