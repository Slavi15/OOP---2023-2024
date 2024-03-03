#include <iostream>
#include <fstream>

unsigned int myStrLen(const char* str)
{
	if (!str) return 0;

	unsigned int count = 0;
	while (*str)
	{
		str++;
		count++;
	}

	return count;
}

char* getReversed(const char* str)
{
	if (!str) return nullptr;

	unsigned length = myStrLen(str);

	char* reversed = new char[length + 1];
	reversed[length] = '\0';

	int idx = 0;
	for (int i = length - 1; i >= 0; i--)
		reversed[idx++] = str[i];

	return reversed;
}

void reverse(std::ifstream& ifs, std::ofstream& ofs)
{
	char buff[1024];

	while (!ifs.eof())
	{
		ifs.getline(buff, 1024);

		char* reversedLine = getReversed(buff);

		ofs << reversedLine << std::endl;

		delete[] reversedLine;
	}
}

void reverseFile(const char* fileName)
{
	if (!fileName) return;

	std::ifstream ifs(fileName);
	if (!ifs.is_open()) return;

	std::ofstream ofs("output.txt");
	if (!ofs.is_open()) return;

	reverse(ifs, ofs);

	ifs.close();
	ofs.close();
}

int main()
{
	reverseFile("input.txt");

	return 0;
}