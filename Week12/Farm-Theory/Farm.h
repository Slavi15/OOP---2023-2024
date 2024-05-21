#pragma once

#include "Animal.h";

class Farm
{
private:
	Animal** container = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	Farm(size_t newSize);
	void resize(size_t newCapacity);

	const unsigned int getNextPowerOfTwo(unsigned int n) const;
	const unsigned int allocateCapacity(unsigned int size) const;

	void copyFrom(const Farm& other);
	void moveFrom(Farm&& other) noexcept;
	void free();

public:
	Farm();

	Farm(const Farm& other);
	Farm& operator=(const Farm& other);

	Farm(Farm&& other) noexcept;
	Farm& operator=(Farm&& other) noexcept;

	const size_t getSize() const;
	const size_t getCapacity() const;

	void addAnimal(AnimalType animalType);
	void addAnimal(const Animal& animal);

	const AnimalType getTypeByIndex(size_t index) const;

	void roarAll() const;

	~Farm() noexcept;
};