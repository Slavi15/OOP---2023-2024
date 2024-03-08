#include <iostream>
#include <fstream>
#include <sstream>

namespace HEXViewerNS
{
	const char hex[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

	struct HEXViewer
	{
		unsigned char* hexArray = nullptr;
		size_t currentSize = 0;
	};

	size_t getFileSize(std::ifstream& ifs)
	{
		size_t currentPosition = ifs.tellg();

		ifs.seekg(0, std::ios::end);
		size_t size = ifs.tellg();

		ifs.seekg(currentPosition);

		return size;
	}

	void decimalToHEX(int n, int base)
	{
		if (n > 0)
		{
			decimalToHEX(n / base, base);
			std::cout << hex[n % base];
		}
	}

	HEXViewer readFromFile(std::ifstream& ifs)
	{
		HEXViewer hex;

		size_t fileSize = getFileSize(ifs);
		hex.currentSize = fileSize;
		hex.hexArray = new unsigned char[fileSize];

		ifs.read((char*)hex.hexArray, fileSize);

		return hex;
	}

	HEXViewer readFromFile(const char* fileName)
	{
		if (!fileName) return HEXViewer{};

		std::ifstream ifs(fileName, std::ios::in | std::ios::binary);
		if (!ifs.is_open()) return HEXViewer{};

		return readFromFile(ifs);
	}

	void printHEXViewer(const HEXViewer& hexViewer)
	{
		for (size_t i = 0; i < hexViewer.currentSize; i++)
		{
			decimalToHEX(hexViewer.hexArray[i], 16);
			std::cout << ' ';
		}

		std::cout << std::endl;

		for (size_t i = 0; i < hexViewer.currentSize; i++)
			std::cout << hexViewer.hexArray[i] << ' ';
	}
}

int main()
{
	HEXViewerNS::HEXViewer hex = HEXViewerNS::readFromFile("sample.txt");

	HEXViewerNS::printHEXViewer(hex);

	delete[] hex.hexArray;

	return 0;
}