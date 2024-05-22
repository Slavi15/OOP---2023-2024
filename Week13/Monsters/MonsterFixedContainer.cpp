#include "MonsterFixedContainer.h"

MonsterFixedContainer::MonsterFixedContainer() = default;

MonsterFixedContainer::MonsterFixedContainer(const MonsterFixedContainer& other)
{
	copyFrom(other);
}

MonsterFixedContainer& MonsterFixedContainer::operator=(const MonsterFixedContainer& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

MonsterFixedContainer::MonsterFixedContainer(MonsterFixedContainer&& other) noexcept
{
	moveFrom(std::move(other));
}

MonsterFixedContainer& MonsterFixedContainer::operator=(MonsterFixedContainer&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const size_t MonsterFixedContainer::getSize() const
{
	return this->size;
}

void MonsterFixedContainer::addMonster(Monster* monster)
{
	if (size >= MAX_COUNT) return;

	this->container[this->size++] = monster;
	monster = nullptr;
}

void MonsterFixedContainer::addMonster(const Monster& monster)
{
	if (size >= MAX_COUNT) return;

	this->container[this->size++] = monster.clone();
}

const Monster& MonsterFixedContainer::operator[](size_t index) const
{
	return *this->container[index];
}

Monster& MonsterFixedContainer::operator[](size_t index)
{
	return *this->container[index];
}

const size_t MonsterFixedContainer::countWins(Monster* monster) const
{
	size_t result = 0;

	for (size_t i = 0; i < getSize(); i++)
		if (monster->beatsMonster(this->container[i]))
			result++;

	return result;
}

MonsterFixedContainer::~MonsterFixedContainer() noexcept
{
	free();
}

void MonsterFixedContainer::copyFrom(const MonsterFixedContainer& other)
{
	this->size = other.size;

	for (size_t i = 0; i < MAX_COUNT; i++)
		if (other.container[i] == nullptr)
			this->container[i] = nullptr;
		else
			this->container[i] = other.container[i]->clone();
}

void MonsterFixedContainer::moveFrom(MonsterFixedContainer&& other) noexcept
{
	this->size = other.size;

	for (size_t i = 0; i < MAX_COUNT; i++)
	{
		this->container[i] = other.container[i];
		other.container[i] = nullptr;
	}
}

void MonsterFixedContainer::free()
{
	for (size_t i = 0; i < MAX_COUNT; i++)
	{
		delete this->container[i];
		this->container[i] = nullptr;
	}

	this->size = 0;
}