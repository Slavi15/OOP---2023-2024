#pragma once

#include "Device.h"

class SmartThermostat : public Device
{
private:
	size_t currentTemperature = 0;
	size_t desiredTemperature = 0;

public:
	virtual void turnOn() const override;
	virtual void turnOff() const override;
	virtual void printDetails() const override;

	SmartThermostat(const char* name, const char* manufacturer, size_t currentTemperature, size_t desiredTemperature);

	const size_t getCurrentTemperature() const;
	const size_t getDesiredTemperature() const;
};