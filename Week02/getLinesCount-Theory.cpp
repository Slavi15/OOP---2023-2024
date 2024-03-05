#include <iostream>
#include <fstream>

size_t getCount(std::ifstream& ifs)
{
	size_t lines = 0;

	char buff[1024];
	while (!ifs.eof())
	{
		ifs.getline(buff, 1024);
		lines++;
	}

	return lines;
}

size_t getLinesCount(const char* fileName)
{
	if (!fileName) return 0;

	std::ifstream ifs(fileName);
	if (!ifs.is_open()) return 0;

	return getCount(ifs);
}

int main()
{
	//std::cout << getLinesCount("sample.txt");

	return 0;
}