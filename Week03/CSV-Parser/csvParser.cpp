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
	//typedef char Field[GLOBAL_CONSTANTS::MAX_FIELD_LENGTH + 1];
	//typedef Field Row[GLOBAL_CONSTANTS::MAX_FIELD_ROWS];

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

	int getColumnIndex(const CSV& csv, const char* title)
	{
		if (!title) return -1;

		for (size_t i = 0; i < csv.currentColumns; i++)
			if (strcmp((char*)&csv.rows[0].field[i], title) == 0)
				return i;

		return -1;
	}

	void modify(CSV& csv, const char* title, const char* newValues, char separator)
	{
		if (!title || !newValues) return;

		int columnIndex = getColumnIndex(csv, title);

		if (columnIndex < 0 || columnIndex > csv.currentColumns) return;

		std::stringstream ss(newValues);

		for (size_t i = 1; i < csv.currentRows && !ss.eof(); i++)
			ss.getline((char*)&csv.rows[i].field[columnIndex], GLOBAL_CONSTANTS::MAX_FIELD_LENGTH, separator);
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

	CSVParserNS::modify(csv, "Name", "Slavi:Angel:Peter", ':');

	CSVParserNS::printCSV(csv);

	CSVParserNS::saveCSV("output.csv", csv);

	return 0;
}