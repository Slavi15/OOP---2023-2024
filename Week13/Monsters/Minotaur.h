#pragma once

#include "Monster.h"

class Minotaur : public Monster
{
public:
	bool beatsMonster(Monster* monster) override;

	bool beatsMinotaur(Minotaur* monster) override;
	bool beatsCentaur(Centaur* monster) override;
	bool beatsSphynx(Sphynx* monster) override;

	Monster* clone() const override;
};