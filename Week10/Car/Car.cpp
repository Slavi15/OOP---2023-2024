#include "Car.h"

Car::Car(const Engine& engine, const Battery& battery, const Tire* tires, const FuelTank& fuelTank, double km, size_t weight) :
	engine(engine), battery(battery), fuelTank(fuelTank)
{
	setTires(tires);
	setKM(km);
	setWeight(weight);
}

Car::Car(Engine&& engine, Battery&& battery, Tire*&& tires, FuelTank&& fuelTank, double km, size_t weight) :
	engine(std::move(engine)), battery(std::move(battery)), fuelTank(std::move(fuelTank))
{
	setTires(std::move(tires));
	setKM(km);
	setWeight(weight);
}

const double Car::getKM() const
{
	return this->km;
}

const size_t Car::getWeight() const
{
	return this->weight;
}

void Car::setKM(double km)
{
	if (km < 0)
		throw std::out_of_range("KM must be positive!");

	this->km = km;
}

void Car::setWeight(size_t weight)
{
	if (weight < 0)
		throw std::out_of_range("Weight must be positive!");

	this->weight = weight;
}

void Car::setTires(const Tire* tires)
{
	if (!tires)
		throw std::runtime_error("NULLPTR!");

	for (size_t i = 0; i < TIRES; i++)
		this->tires[i] = tires[i];
}

void Car::setTires(Tire*&& tires)
{
	if (!tires)
		throw std::runtime_error("NULLPTR!");

	for (size_t i = 0; i < TIRES; i++)
		this->tires[i] = std::move(tires[i]);
}

void Car::drive(double km)
{
	if ((fuelTank.getTankFullness() - km) <= 0)
		throw insufficient_fuel_error("Insufficient tank fullness!");

	this->km += km;
	fuelTank.setTankFullness(fuelTank.getTankFullness() - km);
}

const Car* dragRace(const Car* car1, const Car* car2)
{
	if (!car1 || !car2)
		throw std::runtime_error("NULLPTR!");

	bool car1Condition = (car1->fuelTank.getTankFullness() - RACE_DISTANCE) <= 0;
	bool car2Condition = (car2->fuelTank.getTankFullness() - RACE_DISTANCE) <= 0;

	if (car1Condition)
		return car2;
	else if (car2Condition)
		return car1;
	else if (car1Condition && car2Condition)
		return nullptr;
	else
	{
		if ((car1->getWeight() / car1->engine.getHorsePower()) > (car2->getWeight() / car2->engine.getHorsePower()))
			return car1;
		else
			return car2;
	}
}
