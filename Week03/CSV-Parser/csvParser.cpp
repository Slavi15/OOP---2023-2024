#include <iostream>
#include <fstream>
#include <sstream>

namespace GLOBAL_CONSTANTS
{
	const unsigned int MAX_FIELD_LENGTH = 100;
	const unsigned int MAX_FIELD_ROWS = 10;
	const unsigned int MAX_ROWS_SIZE = 100;
}

namespace CSVParserNS
{
	struct Field
	{
		char field[GLOBAL_CONSTANTS::MAX_FIELD_LENGTH + 1];
	};

	struct Row
	{
		Field field[GLOBAL_CONSTANTS::MAX_FIELD_ROWS];
	};

	struct CSV
	{
		Row rows[GLOBAL_CONSTANTS::MAX_ROWS_SIZE];
		size_t currentRows = 0;
		size_t currentColumns = 0;
	};

	size_t parseRow(const char* buffer, Row& row)
	{
		if (!buffer) return 0;

		std::stringstream ss(buffer);

		size_t currentColumnsCount = 0;
		while (!ss.eof())
			ss.getline((char*)&row.field[currentColumnsCount++], 1024, ',');

		return currentColumnsCount;
	}

	CSV readFromFile(std::ifstream& ifs)
	{
		CSV csvDatabase;

		char buffer[1024];
		while (!ifs.eof())
		{
			ifs.getline(buffer, 1024);
			csvDatabase.currentColumns = parseRow(buffer, csvDatabase.rows[csvDatabase.currentRows++]);
		}

		return csvDatabase;
	}

	CSV readFromFile(const char* fileName)
	{
		if (!fileName) return {};

		std::ifstream ifs(fileName, std::ios::in);
		if (!ifs.is_open()) return {};

		return readFromFile(ifs);
	}

	void saveCSV(std::ofstream& ofs, const CSV& csv)
	{
		for (size_t i = 0; i < csv.currentRows; i++)
		{
			for (size_t j = 0; j < csv.currentColumns; j++)
				ofs << (char*)&csv.rows[i].field[j] << "; ";
			ofs << std::endl;
		}
	}

	void saveCSV(const char* fileName, const CSV& csv)
	{
		if (!fileName) return;

		std::ofstream ofs(fileName);
		if (!ofs.is_open()) return;

		return saveCSV(ofs, csv);
	}

	void printCSV(const CSV& csv)
	{
		for (size_t i = 0; i < csv.currentRows; i++)
		{
			for (size_t j = 0; j < csv.currentColumns; j++)
				std::cout << (char*)&csv.rows[i].field[j] << "   ";
			std::cout << std::endl;
		}
	}
}

int main()
{
	CSVParserNS::CSV csv = CSVParserNS::readFromFile("sample.csv");

	CSVParserNS::printCSV(csv);

	CSVParserNS::saveCSV("output.csv", csv);

	return 0;
}