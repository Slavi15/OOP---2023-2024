#include "MonsterContainer.h"

MonsterContainer::MonsterContainer() : MonsterContainer(4) {}

MonsterContainer::MonsterContainer(size_t newSize) : size(0)
{
	this->capacity = allocateCapacity(newSize);
	this->container = new Monster * [this->capacity];
}

MonsterContainer::MonsterContainer(const MonsterContainer& other)
{
	copyFrom(other);
}

MonsterContainer& MonsterContainer::operator=(const MonsterContainer& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

MonsterContainer::MonsterContainer(MonsterContainer&& other) noexcept
{
	moveFrom(std::move(other));
}

MonsterContainer& MonsterContainer::operator=(MonsterContainer&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const size_t MonsterContainer::getSize() const
{
	return this->size;
}

const size_t MonsterContainer::getCapacity() const
{
	return this->capacity;
}

void MonsterContainer::addMonster(Monster* monster)
{
	if (getSize() >= getCapacity())
		resize(getCapacity() * 2);

	this->container[this->size++] = monster;
	monster = nullptr;
}

void MonsterContainer::addMonster(const Monster& monster)
{
	if (getSize() >= getCapacity())
		resize(getCapacity() * 2);

	this->container[this->size++] = monster.clone();
}

const Monster& MonsterContainer::operator[](size_t index) const
{
	return *this->container[index];
}

Monster& MonsterContainer::operator[](size_t index)
{
	return *this->container[index];
}

const size_t MonsterContainer::countWins(Monster* monster) const
{
	size_t result = 0;

	for (size_t i = 0; i < getSize(); i++)
		if (monster->beatsMonster(this->container[i]))
			result++;

	return result;
}

MonsterContainer::~MonsterContainer() noexcept
{
	free();
}

void MonsterContainer::resize(size_t newCapacity)
{
	Monster** newMonsters = new Monster * [newCapacity];
	for (size_t i = 0; i < getSize(); i++)
		newMonsters[i] = this->container[i];

	delete[] this->container;
	this->container = newMonsters;
	this->capacity = newCapacity;
}

const unsigned int MonsterContainer::getNextPowerOfTwo(unsigned int n) const
{
	if (n == 0) return 1;

	while (n & (n - 1))
		n &= (n - 1);

	return n << 1;
}

const unsigned int MonsterContainer::allocateCapacity(unsigned int size) const
{
	return std::max(getNextPowerOfTwo(size + 1), 8u);
}

void MonsterContainer::copyFrom(const MonsterContainer& other)
{
	this->size = other.size;
	this->capacity = other.capacity;

	this->container = new Monster * [this->capacity];
	for (size_t i = 0; i < this->capacity; i++)
		this->container[i] = other.container[i]->clone();
}

void MonsterContainer::moveFrom(MonsterContainer&& other) noexcept
{
	this->container = other.container;
	this->size = other.size;
	this->capacity = other.capacity;

	other.container = nullptr;
	other.size = other.capacity = 0;
}

void MonsterContainer::free()
{
	for (size_t i = 0; i < this->size; i++)
		delete this->container[i];

	delete[] this->container;
	this->container = nullptr;
	this->size = this->capacity = 0;
}
