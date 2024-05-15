#pragma once

#include "Device.h"

class SmartSpeaker : public Device
{
private:
	size_t soundDB = 0;

public:
	virtual void turnOn() const override;
	virtual void turnOff() const override;
	virtual void printDetails() const override;

	SmartSpeaker(const char* name, const char* manufacturer, size_t soundDB);

	const size_t getSoundDB() const;
};