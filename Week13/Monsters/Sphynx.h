#pragma once

#include "Monster.h"

class Sphynx : public Monster
{
public:
	bool beatsMonster(Monster* monster) override;

	bool beatsSphynx(Sphynx* monster) override;
	bool beatsMinotaur(Minotaur* monster) override;
	bool beatsCentaur(Centaur* monster) override;

	Monster* clone() const override;
};