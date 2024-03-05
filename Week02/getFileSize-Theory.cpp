#include <iostream>
#include <fstream>

size_t getSize(std::ifstream& ifs)
{
	size_t position = ifs.tellg();

	ifs.seekg(0, std::ios::end);
	size_t size = ifs.tellg();

	ifs.seekg(position);
	ifs.clear();

	return size;
}

size_t getFileSize(const char* fileName)
{
	if (!fileName) return 0;

	std::ifstream ifs(fileName);
	if (!ifs.is_open()) return 0;

	return getSize(ifs);
}

int main()
{
	//std::cout << getFileSize("sample.txt");

	return 0;
}