#pragma once
#pragma warning (disable : 4996)

#include <fstream>

#include "CarPart.h"

class Battery : public CarPart
{
private:
	char* batteryID = nullptr;
	size_t batteryCapacity = 0;

	void copyFrom(const Battery& other);
	void moveFrom(Battery&& other) noexcept;
	void free();

public:
	Battery();
	Battery(const char* batteryID, size_t batteryCapacity, size_t ID, const char* manufacturer, const char* description);

	Battery(const Battery& other);
	Battery& operator=(const Battery& other);

	Battery(Battery&& other) noexcept;
	Battery& operator=(Battery&& other) noexcept;

	const char* getBatteryID() const;
	const size_t getBatteryCapacity() const;

	void setBatteryID(const char* batteryID);
	void setBatteryCapacity(size_t batteryCapacity);

	friend std::ostream& operator<<(std::ostream& os, const Battery& battery);

	~Battery() noexcept;
};