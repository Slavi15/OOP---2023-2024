#pragma once

#include "Player.h"

class Guest : protected Player
{
private:
	size_t remainingTime = 0;

public:
	Guest(size_t remainingTime);

	bool levelUp() override;
};