#pragma once

#include <iostream>

#include "Error.h"

class FuelTank
{
private:
	double tankCapacity = 0;
	double tankFullness = 0;

public:
	FuelTank() = default;
	FuelTank(double tankCapacity);

	FuelTank(const FuelTank& other) = default;
	FuelTank& operator=(const FuelTank& other) = default;

	FuelTank(FuelTank&& other) = default;
	FuelTank& operator=(FuelTank&& other) = default;

	const double getTankCapacity() const;
	const double getTankFullness() const;

	void setTankCapacity(double tankCapacity);
	void setTankFullness(double tankFullness);

	void chargeFuel(double fuel);
	void burnFuel(double fuel);
};