#include "Engine.h"

Engine::Engine(size_t horsePower, size_t ID, const char* manufacturer, const char* description) : CarPart(ID, manufacturer, description)
{
	setHorsePower(horsePower);
}

const size_t Engine::getHorsePower() const
{
	return this->horsePower;
}

void Engine::setHorsePower(size_t horsePower)
{
	if (horsePower < 0)
		throw std::out_of_range("Horse power must be positive!");

	this->horsePower = horsePower;
}

std::ostream& operator<<(std::ostream& os, const Engine& engine)
{
	return os << (CarPart)engine << engine.getHorsePower() << " hp" << std::endl;
}