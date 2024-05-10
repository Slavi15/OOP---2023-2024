#include "PremiumPlayer.h"

PremiumPlayer::PremiumPlayer() = default;

PremiumPlayer::PremiumPlayer(const char* username) : Player()
{
	setUsername(username);
}

PremiumPlayer::PremiumPlayer(const PremiumPlayer& other) : Player(other)
{
	copyFrom(other);
}

PremiumPlayer& PremiumPlayer::operator=(const PremiumPlayer& other)
{
	if (this != &other)
	{
		Player::operator=(other);
		free();
		copyFrom(other);
	}

	return *this;
}

PremiumPlayer::PremiumPlayer(PremiumPlayer&& other) noexcept : Player(std::move(other))
{
	moveFrom(std::move(other));
}

PremiumPlayer& PremiumPlayer::operator=(PremiumPlayer&& other) noexcept
{
	if (this != &other)
	{
		Player::operator=(std::move(other));
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

bool PremiumPlayer::levelUp()
{
	if (this->stars == Stars::FIVE)
		return false;

	int currentStars = (int)this->stars;

	if (this->points >= POINTS_BETWEEN_LEVELS)
	{
		this->stars = (Stars)(currentStars + 1);
		this->points -= POINTS_BETWEEN_LEVELS;
		return true;
	}

	return false;
}

const char* PremiumPlayer::getUsername() const
{
	return this->username;
}

void PremiumPlayer::setUsername(const char* username)
{
	if (!username)
		throw std::runtime_error("NULLPTR!");

	this->username = new (std::nothrow) char[strlen(username) + 1];
	strcpy(this->username, username);
}

PremiumPlayer::~PremiumPlayer() noexcept
{
	free();
	// Player::~Player()
}

void PremiumPlayer::copyFrom(const PremiumPlayer& other)
{
	this->username = new char[strlen(other.username) + 1];
	strcpy(this->username, other.username);
}


void PremiumPlayer::moveFrom(PremiumPlayer&& other) noexcept
{
	this->username = other.username;

	other.username = nullptr;
}

void PremiumPlayer::free()
{
	delete[] this->username;

	this->username = nullptr;
}