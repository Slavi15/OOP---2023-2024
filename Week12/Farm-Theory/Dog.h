#pragma once

#include "Animal.h"

class Dog : public Animal
{
public:
	Dog();

	void roar() const override;

	Animal* clone() const override;

	bool mateWith(Animal* animal) override;

	// NOT in Syllabus!!!
	bool mateWithDog(Dog* animal) override;
	bool mateWithCat(Cat* animal) override;
	bool mateWithTiger(Tiger* animal) override;
	// NOT in Syllabus!!!
};