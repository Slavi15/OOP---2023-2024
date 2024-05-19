#include "Animal.h"

Animal::Animal(AnimalType type) : animalType(type) {}

const AnimalType Animal::getType() const
{
	return this->animalType;
}
