#pragma once

#include "Monster.h"

#define MAX_COUNT 15

class MonsterFixedContainer
{
private:
	Monster* container[MAX_COUNT];
	size_t size = 0;

	void copyFrom(const MonsterFixedContainer& other);
	void moveFrom(MonsterFixedContainer&& other) noexcept;
	void free();

public:
	MonsterFixedContainer();

	MonsterFixedContainer(const MonsterFixedContainer& other);
	MonsterFixedContainer& operator=(const MonsterFixedContainer& other);

	MonsterFixedContainer(MonsterFixedContainer&& other) noexcept;
	MonsterFixedContainer& operator=(MonsterFixedContainer&& other) noexcept;

	const size_t getSize() const;

	void addMonster(Monster* monster);
	void addMonster(const Monster& monster);

	const Monster& operator[](size_t index) const;
	Monster& operator[](size_t index);

	const size_t countWins(Monster* monster) const;

	~MonsterFixedContainer() noexcept;
};