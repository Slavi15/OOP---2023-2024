#include "Farm.h"
#include "AnimalFactory.h"

Farm::Farm() : Farm(4) {}

Farm::Farm(size_t newSize) : size(0)
{
	this->capacity = allocateCapacity(newSize);
	this->container = new Animal * [this->capacity];
}

Farm::Farm(const Farm& other)
{
	copyFrom(other);
}

Farm& Farm::operator=(const Farm& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Farm::Farm(Farm&& other) noexcept
{
	moveFrom(std::move(other));
}

Farm& Farm::operator=(Farm&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const size_t Farm::getSize() const
{
	return this->size;
}

const size_t Farm::getCapacity() const
{
	return this->capacity;
}

void Farm::addAnimal(AnimalType animalType)
{
	if (getSize() >= getCapacity())
		resize(getCapacity() * 2);

	this->container[this->size++] = animalFactory(animalType);
}

void Farm::addAnimal(const Animal& animal)
{
	if (getSize() >= getCapacity())
		resize(getCapacity() * 2);

	this->container[this->size++] = animal.clone();
}

const AnimalType Farm::getTypeByIndex(size_t index) const
{
	if (index >= getSize())
		throw std::out_of_range("Invalid index!");

	return this->container[index]->getType();
}

void Farm::roarAll() const
{
	for (size_t i = 0; i < getSize(); i++)
		this->container[i]->roar();
}

void Farm::resize(size_t newCapacity)
{
	Animal** newAnimals = new Animal * [newCapacity];
	for (size_t i = 0; i < getSize(); i++)
		newAnimals[i] = this->container[i];

	delete[] this->container;
	this->container = newAnimals;
	this->capacity = newCapacity;
}

const unsigned int Farm::getNextPowerOfTwo(unsigned int n) const
{
	if (n == 0) return 1;

	while (n & (n - 1))
		n &= (n - 1);

	return n << 1;
}

const unsigned int Farm::allocateCapacity(unsigned int size) const
{
	return std::max(getNextPowerOfTwo(size + 1), 8u);
}

void Farm::copyFrom(const Farm& other)
{
	this->size = other.size;
	this->capacity = other.capacity;

	this->container = new Animal * [this->capacity];
	for (size_t i = 0; i < this->capacity; i++)
		this->container[i] = other.container[i]->clone();
}

void Farm::moveFrom(Farm&& other) noexcept
{
	this->container = other.container;
	this->size = other.size;
	this->capacity = other.capacity;

	other.container = nullptr;
	other.size = other.capacity = 0;
}

void Farm::free()
{
	for (size_t i = 0; i < this->size; i++)
		delete this->container[i];

	delete[] this->container;
	this->container = nullptr;
	this->size = this->capacity = 0;
}

Farm::~Farm() noexcept
{
	free();
}
