#include "LoggedPlayer.h"

LoggedPlayer::LoggedPlayer(const char* password)
{
	setPassword(password);
}

void LoggedPlayer::setPassword(const char* password)
{
	if (!password)
		throw std::runtime_error("NULLPTR!");

	if (strlen(password) > MAX_PASSWORD_LENGTH)
		throw std::invalid_argument("Password must be maximum 8 symbols!");

	strcpy(this->password, password);
}

const bool LoggedPlayer::login(int ID, const char* password) const
{
	if (!password)
		throw std::runtime_error("NULLPTR!");

	return this->getID() == ID && strcmp(this->password, password) == 0; // this->ID == ID
}