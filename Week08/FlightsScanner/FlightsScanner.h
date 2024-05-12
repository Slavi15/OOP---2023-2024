#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include "FlightsRecord.h"
#include "Utils.h"

#define MAX_TEXT 1024

class FlightsScanner
{
private:
	char* inputFile = nullptr;
	char* outputFile = nullptr;

	void copyFrom(const FlightsScanner& other);
	void moveFrom(FlightsScanner&& other) noexcept;
	void free();

	void handleAirport(char* airport) const;

	void parseLine(const char* line, FlightsRecord& record); // accepts line and parses it using stringstream
	void saveRecord(std::ofstream& ofs, const FlightsRecord& record) const;

	bool readExport(std::istream& ifs); // accepts ifstream due to check if  ifs.fail() in  run()

public:
	FlightsScanner();
	FlightsScanner(const char* inputFile, const char* outputFile);

	FlightsScanner(const FlightsScanner& other);
	FlightsScanner& operator=(const FlightsScanner& other);

	FlightsScanner(FlightsScanner&& other) noexcept;
	FlightsScanner& operator=(FlightsScanner&& other) noexcept;

	const char* getInputFile() const;
	const char* getOutputFile() const;

	void setInputFile(const char* inputFile);
	void setOutputFile(const char* outputFile);

	void run();

	~FlightsScanner() noexcept;
};