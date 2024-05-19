#include "AnimalFactory.h"

Animal* animalFactory(AnimalType type)
{
	if (type == AnimalType::CAT)
		return new Cat();
	else if (type == AnimalType::DOG)
		return new Dog();
	else if (type == AnimalType::TIGER)
		return new Tiger();

	return nullptr;
}
