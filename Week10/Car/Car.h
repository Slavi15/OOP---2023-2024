#pragma once

#include "Engine.h"
#include "Battery.h"
#include "Tire.h"
#include "FuelTank.h"

#include "Error.h"

#define TIRES 4
#define RACE_DISTANCE 0.4

class Car
{
private:
	Engine engine;
	Battery battery;
	Tire tires[TIRES];
	FuelTank fuelTank;
	double km = 0;
	size_t weight = 0;

public:
	Car(const Engine& engine, const Battery& battery, const Tire* tires, const FuelTank& fuelTank, double km, size_t weight);
	Car(Engine&& engine, Battery&& battery, Tire*&& tires, FuelTank&& fuelTank, double km, size_t weight);

	const double getKM() const;
	const size_t getWeight() const;

	void setKM(double km);
	void setWeight(size_t weight);

	void setTires(const Tire* tires);
	void setTires(Tire*&& tires);

	void drive(double km);

	friend const Car* dragRace(const Car* car1, const Car* car2);
};