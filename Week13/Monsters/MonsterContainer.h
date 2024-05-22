#pragma once

#include "Monster.h"

class MonsterContainer
{
private:
	Monster** container = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	MonsterContainer(size_t newSize);
	void resize(size_t newCapacity);

	const unsigned int getNextPowerOfTwo(unsigned int n) const;
	const unsigned int allocateCapacity(unsigned int size) const;

	void copyFrom(const MonsterContainer& other);
	void moveFrom(MonsterContainer&& other) noexcept;
	void free();

public:
	MonsterContainer();

	MonsterContainer(const MonsterContainer& other);
	MonsterContainer& operator=(const MonsterContainer& other);

	MonsterContainer(MonsterContainer&& other) noexcept;
	MonsterContainer& operator=(MonsterContainer&& other) noexcept;

	const size_t getSize() const;
	const size_t getCapacity() const;

	void addMonster(Monster* monster);
	void addMonster(const Monster& monster);

	const Monster& operator[](size_t index) const;
	Monster& operator[](size_t index);

	const size_t countWins(Monster* monster) const;

	~MonsterContainer() noexcept;
};