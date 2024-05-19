#include "Dog.h"

Dog::Dog() : Animal(AnimalType::DOG) {}

void Dog::roar() const
{
	std::cout << "Woof! Woof!" << std::endl;
}

Animal* Dog::clone() const
{
	return new Dog(*this);
}

bool Dog::mateWith(Animal* animal)
{
	return animal->mateWithDog(this);
}

bool Dog::mateWithDog(Dog* animal)
{
	std::cout << "Dog + Dog" << std::endl;
	return true;
}

bool Dog::mateWithCat(Cat* animal)
{
	std::cout << "Dog + Cat" << std::endl;
	return true;
}

bool Dog::mateWithTiger(Tiger* animal)
{
	std::cout << "Dog + Tiger" << std::endl;
	return true;
}
