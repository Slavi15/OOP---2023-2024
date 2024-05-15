#include "SmartSpeaker.h"

void SmartSpeaker::turnOn() const
{
	std::cout << "Smart Speaker ON!" << std::endl;
}

void SmartSpeaker::turnOff() const
{
	std::cout << "Smart Speaker OFF!" << std::endl;
}

void SmartSpeaker::printDetails() const
{
	Device::printDetails();
	std::cout << "Sound: " << getSoundDB() << std::endl;
}

SmartSpeaker::SmartSpeaker(const char* name, const char* manufacturer, size_t soundDB) : Device(name, manufacturer), soundDB(soundDB) {}

const size_t SmartSpeaker::getSoundDB() const
{
	return this->soundDB;
}
