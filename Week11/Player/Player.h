#pragma once

#include <iostream>

#define POINTS_BETWEEN_LEVELS 256

#define powerOfTwo(n) (1 << n)

enum class Stars { ONE = 0, TWO, THREE, FOUR, FIVE };

class Player
{
protected:
	int ID = 0;
	size_t points = 0;
	Stars stars = Stars::ONE;

	static int idCounter;

public:
	Player();

	virtual bool levelUp() = 0;

	const int getID() const;
	const size_t getPoints() const;
	Stars getStars() const;

	void addPoints(int points);

	virtual ~Player() noexcept;
};