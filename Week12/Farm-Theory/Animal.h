#pragma once

#include <iostream>

class Cat;
class Dog;
class Tiger;

enum class AnimalType { CAT, DOG, TIGER };

class Animal
{
private:
	AnimalType animalType;

public:
	Animal(AnimalType type);

	virtual void roar() const = 0;

	const AnimalType getType() const;

	virtual Animal* clone() const = 0;

	virtual bool mateWith(Animal* animal) = 0;

	// NOT in Syllabus!!!
	virtual bool mateWithCat(Cat* animal) = 0;
	virtual bool mateWithDog(Dog* animal) = 0;
	virtual bool mateWithTiger(Tiger* animal) = 0;
	// NOT in Syllabus!!!

	virtual ~Animal() noexcept = default;
};