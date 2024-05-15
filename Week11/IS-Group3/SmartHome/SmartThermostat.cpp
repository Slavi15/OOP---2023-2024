#include "SmartThermostat.h"

void SmartThermostat::turnOn() const
{
    std::cout << "Smart Thermostat ON!" << std::endl;
}

void SmartThermostat::turnOff() const
{
    std::cout << "Smart Thermostat OFF!" << std::endl;
}

void SmartThermostat::printDetails() const
{
    Device::printDetails();
    std::cout << "Current Temperature: " << getCurrentTemperature() << std::endl;
    std::cout << "Desired Temperature: " << getDesiredTemperature() << std::endl;
}

SmartThermostat::SmartThermostat(const char* name, const char* manufacturer, size_t currentTemperature, size_t desiredTemperature) : 
    Device(name, manufacturer), currentTemperature(currentTemperature), desiredTemperature(desiredTemperature) {}

const size_t SmartThermostat::getCurrentTemperature() const
{
    return this->currentTemperature;
}

const size_t SmartThermostat::getDesiredTemperature() const
{
    return this->desiredTemperature;
}
