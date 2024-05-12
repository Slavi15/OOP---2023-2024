#include "FlightsScanner.h"

FlightsScanner::FlightsScanner() = default;

FlightsScanner::FlightsScanner(const char* inputFile, const char* outputFile)
{
	if (!inputFile || !outputFile)
		throw std::runtime_error("NULLPTR!");

	setInputFile(inputFile);
	setOutputFile(outputFile);
}

FlightsScanner::FlightsScanner(const FlightsScanner& other)
{
	copyFrom(other);
}

FlightsScanner& FlightsScanner::operator=(const FlightsScanner& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

FlightsScanner::FlightsScanner(FlightsScanner&& other) noexcept
{
	moveFrom(std::move(other));
}

FlightsScanner& FlightsScanner::operator=(FlightsScanner&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

void FlightsScanner::parseLine(const char* line, FlightsRecord& record)
{
	if (!line)
		throw std::runtime_error("NULLPTR!");

	std::stringstream ss(line);

	char data[MAX_TEXT + 1];

	ss.getline(data, MAX_TEXT + 1, ' ');
	record.setOrigin(data);

	try
	{
		handleAirport((char*)record.getOrigin());
	}
	catch (const std::length_error& exc)
	{
		std::cout << "Error: " << exc.what() << std::endl;
	}
	catch (const std::runtime_error& exc)
	{
		std::cout << "Error: " << exc.what() << std::endl;
	}

	ss.getline(data, MAX_TEXT + 1, ' ');
	record.setDestination(data);

	try
	{
		handleAirport((char*)record.getDestination());
	}
	catch (const std::length_error& exc)
	{
		std::cout << "Error: " << exc.what() << std::endl;
	}
	catch (const std::runtime_error& exc)
	{
		std::cout << "Error: " << exc.what() << std::endl;
	}

	ss.getline(data, MAX_TEXT + 1, '\n');
	
	try
	{
		record.setPrize(convertToNum(data));
	}
	catch (const std::bad_cast& exc)
	{
		static constexpr size_t DEFAULT_AMOUNT = 50;
		std::cout << "Invalid amount! Setting to default: " << DEFAULT_AMOUNT << std::endl;
		record.setPrize(DEFAULT_AMOUNT);
		throw;
	}
}

void FlightsScanner::saveRecord(std::ofstream& ofs, const FlightsRecord& record) const
{
	static constexpr size_t EU_TO_LEV = 2;
	ofs << record.getOrigin() << " " << record.getDestination() << " " << record.getPrize() * EU_TO_LEV << std::endl;
}

bool FlightsScanner::readExport(std::istream& ifs)
{
	std::ofstream ofs(this->outputFile, std::ios::out | std::ios::app);

	if (!ofs.is_open())
		throw std::runtime_error("Error opening file!");

	while (!ifs.eof())
	{
		char line[MAX_TEXT + 1];
		ifs.getline(line, MAX_TEXT + 1, '\n');

		FlightsRecord record;

		try
		{
			parseLine(line, record);
			saveRecord(ofs, record);
		}
		catch (const std::invalid_argument& exc)
		{
			std::cout << "Error: " << exc.what() << ". The flight will NOT be saved! " << std::endl;
			return false;
		}
		catch (const std::length_error& exc)
		{
			std::cout << "Error: " << exc.what() << ". The flight will NOT be saved! " << std::endl;
			return false;
		}
		catch (const std::bad_cast& exc)
		{
			std::cout << "Error: " << exc.what() << ". The flight will be saved! " << std::endl;
			saveRecord(ofs, record);
		}
		catch (const std::exception& exc)
		{
			std::cout << "Error: " << exc.what() << ". The flight will NOT be saved! " << std::endl;
			return false;
		}
		catch (...)
		{
			std::cout << "The flight will NOT be saved!" << std::endl;
			return false;
		}
	}

	return true;
}

void FlightsScanner::run()
{
	std::ifstream ifs(this->inputFile, std::ios::in);

	if (!ifs.fail())
	{
		std::cout << "File found!" << std::endl;

		if (!ifs.is_open())
			throw std::runtime_error("Error opening file!");

		if (readExport(ifs))
			std::cout << "Successfully exported file!" << std::endl;
		else
			std::cout << "Error exporting the file!" << std::endl;

		ifs.close();
	}
	else
	{
		std::cout << "File not found!" << std::endl;
	}
}

const char* FlightsScanner::getInputFile() const
{
	return this->inputFile;
}

const char* FlightsScanner::getOutputFile() const
{
	return this->outputFile;
}

void FlightsScanner::setInputFile(const char* inputFile)
{
	if (!inputFile)
		throw std::runtime_error("NULLPTR!");

	this->inputFile = new (std::nothrow) char[strlen(inputFile) + 1];
	strcpy(this->inputFile, inputFile);
}

void FlightsScanner::setOutputFile(const char* outputFile)
{
	if (!outputFile)
		throw std::runtime_error("NULLPTR!");

	this->outputFile = new (std::nothrow) char[strlen(outputFile) + 1];
	strcpy(this->outputFile, outputFile);
}

FlightsScanner::~FlightsScanner() noexcept
{
	free();
}

void FlightsScanner::copyFrom(const FlightsScanner& other)
{
	this->inputFile = new char[strlen(other.inputFile) + 1];
	strcpy(this->inputFile, other.inputFile);

	this->outputFile = new char[strlen(other.outputFile) + 1];
	strcpy(this->outputFile, other.outputFile);
}

void FlightsScanner::moveFrom(FlightsScanner&& other) noexcept
{
	this->inputFile = other.inputFile;
	this->outputFile = other.outputFile;

	other.inputFile = nullptr;
	other.outputFile = nullptr;
}

void FlightsScanner::free()
{
	delete[] this->inputFile;
	delete[] this->outputFile;

	this->inputFile = nullptr;
	this->outputFile = nullptr;
}

void FlightsScanner::handleAirport(char* airport) const
{
	if (!airport)
		throw std::runtime_error("NULLPTR!");

	if (strlen(airport) != 3)
		throw std::length_error("Airport length must be 3 symbols!");

	toUpper(airport);
}
