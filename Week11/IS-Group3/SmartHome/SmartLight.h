#pragma once

#include "Device.h"

class SmartLight : public Device
{
private:
	size_t brightness = 0;

public:
	virtual void turnOn() const override;
	virtual void turnOff() const override;
	virtual void printDetails() const override;

	SmartLight(const char* name, const char* manufacturer, size_t brightness);

	const size_t getBrightness() const;

	void setBrightness(size_t brightness);
};