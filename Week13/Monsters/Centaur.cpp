#include "Centaur.h"

bool Centaur::beatsMonster(Monster* monster)
{
	return monster->beatsCentaur(this);
}

bool Centaur::beatsCentaur(Centaur* monster)
{
	throw drinking_beer("Drinking Beer!");
}

bool Centaur::beatsMinotaur(Minotaur* monster)
{
	std::cout << "Centaur beats Minotaur" << std::endl;
	return true;
}

bool Centaur::beatsSphynx(Sphynx* monster)
{
	std::cout << "Sphynx beats Centaur!" << std::endl;
	return false;
}

Monster* Centaur::clone() const
{
	return new Centaur(*this);
}
