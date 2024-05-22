#include "Minotaur.h"

bool Minotaur::beatsMonster(Monster* monster)
{
	return monster->beatsMinotaur(this);
}

bool Minotaur::beatsMinotaur(Minotaur* monster)
{
	throw drinking_beer("Drinking Beer!");
}

bool Minotaur::beatsCentaur(Centaur* monster)
{
	std::cout << "Centaur beats Minotaur!" << std::endl;
	return false;
}

bool Minotaur::beatsSphynx(Sphynx* monster)
{
	std::cout << "Minotaur beats Sphynx!" << std::endl;
	return true;
}

Monster* Minotaur::clone() const
{
	return new Minotaur(*this);
}
