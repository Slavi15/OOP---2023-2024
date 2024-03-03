#include <iostream>
#include <fstream>

void selfPrinting(const char* fileName)
{
	if (!fileName)
		return;

	std::ifstream ifs(fileName);

	if (!ifs.is_open())
		return;

	char buffer[1024];
	while (!ifs.eof())
	{
		ifs.getline(buffer, 1024);
		std::cout << buffer << std::endl;
	}

	ifs.close();
}

int main()
{
	selfPrinting("main.cpp");

	return 0;
}