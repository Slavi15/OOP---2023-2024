#pragma once

#include <fstream>

#include "CarPart.h"

#define MIN_TIRE_WIDTH 155
#define MAX_TIRE_WIDTH 365

#define MIN_TIRE_PROFILE 30
#define MAX_TIRE_PROFILE 80

#define MIN_TIRE_DIAMETER 13
#define MAX_TIRE_DIAMETER 21

class Tire : public CarPart
{
private:
	size_t tireWidth = 0;
	size_t tireProfile = 0;
	size_t tireDiameter = 0;

public:
	Tire() = default;
	Tire(size_t tireWidth, size_t tireProfile, size_t tireDiameter, size_t ID, const char* manufacturer, const char* description);

	Tire(const Tire& other) = default;
	Tire& operator=(const Tire& other) = default;

	Tire(Tire&& other) = default;
	Tire& operator=(Tire&& other) = default;

	const size_t getTireWidth() const;
	const size_t getTireProfile() const;
	const size_t getTireDiameter() const;

	void setTireWidth(size_t tireWidth);
	void setTireProfile(size_t tireProfile);
	void setTireDiameter(size_t tireDiameter);

	friend std::ostream& operator<<(std::ostream& os, const Tire& tire);
};