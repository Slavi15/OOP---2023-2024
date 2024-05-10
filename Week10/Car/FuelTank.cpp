#include "FuelTank.h"

FuelTank::FuelTank(double tankCapacity)
{
	setTankCapacity(tankCapacity);
	setTankFullness(tankCapacity);
}

const double FuelTank::getTankCapacity() const
{
	return this->tankCapacity;
}

const double FuelTank::getTankFullness() const
{
	return this->tankFullness;
}

void FuelTank::setTankCapacity(double tankCapacity)
{
	if (tankCapacity < 0)
		throw std::out_of_range("Tank capacity should be positive!");

	this->tankCapacity = tankCapacity;
}

void FuelTank::setTankFullness(double tankFullness)
{
	if (tankFullness < 0)
		throw std::out_of_range("Tank fullness must be positive!");

	this->tankFullness = tankFullness;
}

void FuelTank::chargeFuel(double fuel)
{
	if ((this->tankFullness + fuel) >= getTankCapacity())
	{
		this->tankFullness = this->tankCapacity;
		return;
	}
	
	this->tankFullness += fuel;
}

void FuelTank::burnFuel(double fuel)
{
	if ((this->tankFullness - fuel) <= 0)
		throw insufficient_fuel_error("Insufficient fuel amount!");

	this->tankFullness -= fuel;
}
