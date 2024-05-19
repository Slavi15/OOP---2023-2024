#include "Cat.h"

Cat::Cat() : Animal(AnimalType::CAT) {}

void Cat::roar() const
{
	std::cout << "Meow! Meow!" << std::endl;
}

Animal* Cat::clone() const
{
	return new Cat(*this);
}

bool Cat::mateWith(Animal* animal)
{
	return animal->mateWithCat(this);
}

bool Cat::mateWithCat(Cat* animal)
{
	std::cout << "Cat + Cat" << std::endl;
	return true;
}

bool Cat::mateWithDog(Dog* animal)
{
	std::cout << "Cat + Dog" << std::endl;
	return true;
}

bool Cat::mateWithTiger(Tiger* animal)
{
	std::cout << "Cat + Tiger" << std::endl;
	return true;
}
