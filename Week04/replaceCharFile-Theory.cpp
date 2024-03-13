#include <iostream>
#include <fstream>

void replaceCharacters(std::fstream& fs, char ch1, char ch2)
{
	while (!fs.eof())
	{
		char current = fs.get();

		if (current == ch1)
		{
			fs.seekg(-1, std::ios::cur);
			fs.put(ch2);
			fs.flush();
		}
	}
}

void replaceCharacters(const char* fileName, char ch1, char ch2)
{
	if (!fileName) return;

	std::fstream fs(fileName, std::ios::in | std::ios::out);
	if (!fs.is_open()) return;

	return replaceCharacters(fs, ch1, ch2);
}

int main()
{
	replaceCharacters("sample.txt", 'a', 'A');

	return 0;
}