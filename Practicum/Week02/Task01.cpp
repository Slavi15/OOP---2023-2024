#include <iostream>
#include <fstream>

namespace FilesNS
{
	int getSubtract(int a, int b)
	{
		return a - b;
	}

	void writeToFile(const char* fileName)
	{
		if (!fileName)
			return;

		std::ofstream outFile(fileName);

		if (!outFile.is_open())
			return;

		int x, y, z;
		std::cin >> x >> y >> z;

		int sum = x + y + z;
		int mult = x * y * z;

		outFile << sum << ' ' << mult;

		outFile.close();
	}

	int readFromFile(const char* fileName)
	{
		if (!fileName)
			return -1;

		std::ifstream inFile(fileName);

		if (!inFile.is_open())
			return -1;

		int x, y;
		inFile >> x >> y;

		inFile.close();

		return getSubtract(x, y);
	}
}

int main()
{
	FilesNS::writeToFile("result.txt");
	std::cout << FilesNS::readFromFile("result.txt");

	return 0;
}