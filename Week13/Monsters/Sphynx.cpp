#include "Sphynx.h"

bool Sphynx::beatsMonster(Monster* monster)
{
	return monster->beatsSphynx(this);
}

bool Sphynx::beatsSphynx(Sphynx* monster)
{
	//throw drinking_beer("Drinking Beer!");
	return false;
}

bool Sphynx::beatsMinotaur(Minotaur* monster)
{
	std::cout << "Minotaur beats Sphynx!" << std::endl;
	return false;
}

bool Sphynx::beatsCentaur(Centaur* monster)
{
	std::cout << "Sphynx beats Centaur!" << std::endl;
	return true;
}

Monster* Sphynx::clone() const
{
	return new Sphynx(*this);
}
