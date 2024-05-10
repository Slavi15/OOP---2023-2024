#pragma once

#include "Player.h"

#define MAX_PASSWORD_LENGTH 8

class LoggedPlayer : protected Player
{
private:
	char password[MAX_PASSWORD_LENGTH + 1];

public:
	LoggedPlayer(const char* password);

	void setPassword(const char* password);

	const bool login(int ID, const char* password) const;
};