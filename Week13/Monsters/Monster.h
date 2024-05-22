#pragma once

#include "drinking_beer.h"

class Minotaur;
class Centaur;
class Sphynx;

class Monster
{
public:
	virtual bool beatsMonster(Monster* monster) = 0;

	virtual bool beatsMinotaur(Minotaur* monster) = 0;
	virtual bool beatsCentaur(Centaur* monster) = 0;
	virtual bool beatsSphynx(Sphynx* monster) = 0;

	virtual Monster* clone() const = 0;

	virtual ~Monster() noexcept = default;
};