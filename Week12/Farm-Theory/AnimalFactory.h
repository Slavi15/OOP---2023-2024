#pragma once

#include "Animal.h"

#include "Cat.h"
#include "Dog.h"
#include "Tiger.h"

Animal* animalFactory(AnimalType type); // important to be only a function, because otherwise it has to be instantiated with a class!!!