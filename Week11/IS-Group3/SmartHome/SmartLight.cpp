#include "SmartLight.h"

SmartLight::SmartLight(const char* name, const char* manufacturer, size_t brightness) : Device(name, manufacturer), brightness(brightness) {}

void SmartLight::turnOn() const
{
	std::cout << "Smart Light ON!" << std::endl;
}

void SmartLight::turnOff() const
{
	std::cout << "Smart Light OFF!" << std::endl;
}

void SmartLight::printDetails() const
{
	Device::printDetails();
	std::cout << "Brightness: " << getBrightness() << std::endl;
}

const size_t SmartLight::getBrightness() const
{
	return this->brightness;
}

void SmartLight::setBrightness(size_t brightness)
{
	this->brightness = brightness;
}
