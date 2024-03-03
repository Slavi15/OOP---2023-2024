#include <iostream>
#include <fstream>

void copy(std::ifstream& ifs, std::ofstream& ofs)
{
	char buffer[1024];
	while (!ifs.eof())
	{
		ifs.getline(buffer, 1024);
		ofs << buffer << std::endl;
	}
}

void copyFromFileToFile(const char* src, const char* dest)
{
	if (!src || !dest)
		return;

	std::ifstream ifs(src);
	if (!ifs.is_open()) return;

	std::ofstream ofs(dest);
	if (!ofs.is_open()) return;

	copy(ifs, ofs);

	ifs.close();
	ofs.close();
}

int main()
{
	copyFromFileToFile("main.cpp", "output.txt");

	return 0;
}