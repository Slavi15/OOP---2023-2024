#include "Tire.h"

Tire::Tire(size_t tireWidth, size_t tireProfile, size_t tireDiameter, size_t ID, const char* manufacturer, const char* description) : CarPart(ID, manufacturer, description)
{
	setTireWidth(tireWidth);
	setTireProfile(tireProfile);
	setTireDiameter(tireDiameter);
}

const size_t Tire::getTireWidth() const
{
	return this->tireWidth;
}

const size_t Tire::getTireProfile() const
{
	return this->tireProfile;
}

const size_t Tire::getTireDiameter() const
{
	return this->tireDiameter;
}

void Tire::setTireWidth(size_t tireWidth)
{
	if (tireWidth < MIN_TIRE_WIDTH || tireWidth > MAX_TIRE_WIDTH)
		throw std::out_of_range("Invalid tire width dimensions!");

	this->tireWidth = tireWidth;
}

void Tire::setTireProfile(size_t tireProfile)
{
	if (tireProfile < MIN_TIRE_PROFILE || tireProfile > MAX_TIRE_PROFILE)
		throw std::out_of_range("Invalid tire profile dimensions!");

	this->tireProfile = tireProfile;
}

void Tire::setTireDiameter(size_t tireDiameter)
{
	if (tireDiameter < MIN_TIRE_DIAMETER || tireDiameter > MAX_TIRE_DIAMETER)
		throw std::out_of_range("Invalid tire diameter dimensions!");

	this->tireDiameter = tireDiameter;
}

std::ostream& operator<<(std::ostream& os, const Tire& tire)
{
	return os << (CarPart)tire << tire.getTireWidth() << "/" << tire.getTireProfile() << "R" << tire.getTireDiameter() << std::endl;
}