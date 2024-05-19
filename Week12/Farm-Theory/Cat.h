#pragma once

#include "Animal.h"

class Cat : public Animal
{
public:
	Cat();

	void roar() const override;

	Animal* clone() const override;

	bool mateWith(Animal* animal) override;

	// NOT in Syllabus!!!
	bool mateWithCat(Cat* animal) override;
	bool mateWithDog(Dog* animal) override;
	bool mateWithTiger(Tiger* animal) override;
	// NOT in Syllabus!!!
};