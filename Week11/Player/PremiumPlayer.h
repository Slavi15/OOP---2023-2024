#pragma once

#include "Player.h"

class PremiumPlayer : protected Player
{
private:
	char* username = nullptr;

	void copyFrom(const PremiumPlayer& other);
	void moveFrom(PremiumPlayer&& other) noexcept;
	void free();

public:
	PremiumPlayer();
	PremiumPlayer(const char* username);

	bool levelUp() override;

	PremiumPlayer(const PremiumPlayer& other);
	PremiumPlayer& operator=(const PremiumPlayer& other);

	PremiumPlayer(PremiumPlayer&& other) noexcept;
	PremiumPlayer& operator=(PremiumPlayer&& other) noexcept;

	const char* getUsername() const;
	void setUsername(const char* username);

	virtual ~PremiumPlayer() noexcept override;
};