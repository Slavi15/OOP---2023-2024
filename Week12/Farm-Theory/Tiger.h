#pragma once

#include "Animal.h"

class Tiger : public Animal
{
public:
	Tiger();

	void roar() const override;

	Animal* clone() const override;

	bool mateWith(Animal* animal) override;

	// NOT in Syllabus!!!
	bool mateWithTiger(Tiger* animal) override;
	bool mateWithCat(Cat* animal) override;
	bool mateWithDog(Dog* animal) override;
	// NOT in Syllabus!!!
};