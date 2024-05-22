#pragma once

#include "Monster.h"

class Centaur : public Monster
{
public:
	bool beatsMonster(Monster* monster)  override;

	bool beatsCentaur(Centaur* monster)  override;
	bool beatsMinotaur(Minotaur* monster)  override;
	bool beatsSphynx(Sphynx* monster)  override;

	Monster* clone() const override;
};