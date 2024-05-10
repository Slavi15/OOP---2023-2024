#include "Player.h"

int Player::idCounter = 0;

Player::Player()
{
	this->ID = idCounter;
	idCounter++;
}

const int Player::getID() const
{
	return this->ID;
}

const size_t Player::getPoints() const
{
	return this->points;
}

Stars Player::getStars() const
{
	return this->stars;
}

void Player::addPoints(int points)
{
	this->points += points;
}

bool Player::levelUp()
{
	if (this->stars == Stars::FIVE)
		return false;

	int currentStars = (int)stars;
	size_t neededPoints = POINTS_BETWEEN_LEVELS * powerOfTwo(currentStars);

	// 256 * 2^0 = 256 - 1 star, 0 in Stars enum
	// 256 * 2^1 = 512 - 2 stars, 1 in Stars enum
	// ...

	if (this->points >= neededPoints)
	{
		this->stars = (Stars)(currentStars + 1);
		this->points -= neededPoints;
		return true;
	}

	return false;
}

Player::~Player() noexcept = default;