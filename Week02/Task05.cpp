#include <iostream>
#include <fstream>

void replace(std::ifstream& ifs, std::ofstream& ofs, std::ifstream& placeholderStream)
{
	char buff[1024];

	while (true)
	{
		char current = ifs.get();

		if (ifs.eof()) break;

		if (current != '{')
			ofs << current;
		else
		{
			placeholderStream.getline(buff, 1024, ' ');
			placeholderStream.getline(buff, 1024, '\n');

			ofs << buff;

			ifs.getline(buff, 1024, '}');
		}
	}
}

void replacePlaceholders(const char* src, const char* dest, const char* placeholder)
{
	if (!src || !dest || !placeholder)
		return;

	std::ifstream ifs(src);
	std::ifstream placeholderStream(placeholder);

	if (!ifs.is_open() && !placeholderStream.is_open()) return;

	std::ofstream ofs(dest);
	if (!ofs.is_open()) return;

	replace(ifs, ofs, placeholderStream);

	ifs.close();
	ofs.close();
	placeholderStream.close();
}

int main()
{
	replacePlaceholders("template.txt", "result.txt", "placeholder.txt");

	return 0;
}