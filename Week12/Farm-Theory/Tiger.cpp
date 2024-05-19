#include "Tiger.h"

Tiger::Tiger() : Animal(AnimalType::TIGER) {}

void Tiger::roar() const
{
	std::cout << "Roar!" << std::endl;
}

Animal* Tiger::clone() const
{
	return new Tiger(*this);
}

bool Tiger::mateWith(Animal* animal)
{
	return animal->mateWithTiger(this);
}

bool Tiger::mateWithTiger(Tiger* animal)
{
	std::cout << "Tiger + Tiger" << std::endl;
	return true;
}

bool Tiger::mateWithCat(Cat* animal)
{
	std::cout << "Tiger + Cat" << std::endl;
	return true;
}

bool Tiger::mateWithDog(Dog* animal)
{
	std::cout << "Tiger + Dog" << std::endl;
	return true;
}
