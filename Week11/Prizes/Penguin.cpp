#include "Penguin.h"

Penguin::Penguin()
{
	setPoints(50);
}

const char* Penguin::visualize() const
{
	writeToFile();
	return "Penguin";
}

void Penguin::writeToFile(std::ofstream& ofs) const
{
	ofs << "Penguin:" << getPoints() << ":" << getPrice();
}

void Penguin::writeToFile() const
{
	std::ofstream ofs("viz/penguin.txt", std::ios::out);

	if (!ofs.is_open())
		throw std::runtime_error("Could not open file!");

	return writeToFile(ofs);
}
