#pragma once

#include "Prize.h"

class Penguin : public Prize
{
private:
	void writeToFile(std::ofstream& ofs) const;

public:
	Penguin();

	const char* visualize() const override;

	void writeToFile() const;
};