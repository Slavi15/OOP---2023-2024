#pragma once

#include <iostream>

class Computer
{
private:
	char* GPUModel = nullptr;
	double CPUPower = 0;
	size_t powerSupply = 0;
	size_t RAM = 0;

	void copyFrom(const Computer& other);
	void moveFrom(Computer&& other) noexcept;
	void free();

public:
	Computer();
	Computer(const char* GPUModel, double CPUPower, size_t powerSupply, size_t RAM);
	
	virtual const char* getComputerType() const = 0;
	virtual const char* getGadgets() const = 0;
	
	Computer(const Computer& other);
	Computer& operator=(const Computer& other);
	
	Computer(Computer&& other) noexcept;
	Computer& operator=(Computer&& other) noexcept;
	
	const char* getGPUModel() const;
	const double getCPUPower() const;
	const size_t getPowerSupply() const;
	const size_t getRAM() const;
	
	void setGPUModel(const char* GPUModel);
	void setCPUPower(double CPUPower);
	void setPowerSupply(size_t powerSupply);
	void setRAM(size_t RAM);
	
	virtual ~Computer() noexcept;
};