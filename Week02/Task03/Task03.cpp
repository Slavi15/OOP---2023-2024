#include <iostream>
#include <fstream>

namespace ColorsNS
{
	struct Color
	{
		unsigned char R, G, B;
	};

	struct Colors
	{
		Color color[5];
		size_t size;
	};

	unsigned powerofTwo(int n)
	{
		return 1 << n;
	}

	unsigned int charToDigit(char ch)
	{
		return ch - '0';
	}

	void decimalToRGB(Color& color, int num)
	{
		color.R = num / powerofTwo(16);
		color.G = (num / powerofTwo(8)) % powerofTwo(8);
		color.B = num % powerofTwo(8);
	}

	unsigned int rgbToDecimal(int r, int g, int b)
	{
		return b + (g * powerofTwo(8)) + (r * powerofTwo(16));
	}

	void parseColor(std::ifstream& ifs, Color& color)
	{
		int num = 0;

		while (true)
		{
			char current = ifs.get();

			if (current != '|' && !ifs.eof())
				(num *= 10) += charToDigit(current);
			else
			{
				decimalToRGB(color, num);
				break;
			}
		}
	}

	void readColors(const char* fileName, Colors& colors)
	{
		if (!fileName)
			return;

		std::ifstream ifs(fileName);

		ifs >> colors.size;
		ifs.ignore();

		if (!ifs.is_open())
			return;

		for (size_t i = 0; i < colors.size; i++)
			parseColor(ifs, colors.color[i]);

		ifs.close();
	}

	void writeColor(std::ofstream& ofs, const Color& color)
	{
		ofs << rgbToDecimal(color.R, color.G, color.B) << '|';
	}

	void writeColors(const char* fileName, const Colors& colors)
	{
		if (!fileName)
			return;

		std::ofstream ofs(fileName);

		if (!ofs.is_open())
			return;

		ofs << colors.size << ' ';

		for (size_t i = 0; i < colors.size; i++)
			writeColor(ofs, colors.color[i]);

		ofs.close();
	}

	void writeRedColors(const char* fileName, const Colors& colors)
	{
		if (!fileName)
			return;

		std::ofstream ofs(fileName);

		if (!ofs.is_open())
			return;

		for (size_t i = 0; i < colors.size; i++)
			if (colors.color[i].R > 250)
				writeColor(ofs, colors.color[i]);

		ofs.close();
	}

	void printColors(const Colors& colors)
	{
		for (size_t i = 0; i < colors.size; i++)
			std::cout << (int)colors.color[i].R << ' ' << (int)colors.color[i].G << ' ' << (int)colors.color[i].B << std::endl;
	}
}

int main()
{
	ColorsNS::Colors colors = { 0 };
	ColorsNS::readColors("colors.txt", colors);
	ColorsNS::writeColors("colors.txt", colors);
	ColorsNS::writeRedColors("red.txt", colors);
	ColorsNS::printColors(colors);

	return 0;
}