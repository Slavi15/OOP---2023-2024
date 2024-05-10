#include "Computer.h"

Computer::Computer() = default;

Computer::Computer(const char* GPUModel, double CPUPower, size_t powerSupply, size_t RAM)
{
	setGPUModel(GPUModel);
	setCPUPower(CPUPower);
	setPowerSupply(powerSupply);
	setRAM(RAM);
}

Computer::Computer(const Computer& other)
{
	copyFrom(other);
}

Computer& Computer::operator=(const Computer& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	
	return *this;
}

Computer::Computer(Computer&& other) noexcept
{
	moveFrom(std::move(other));
}

Computer& Computer::operator=(Computer&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	
	return *this;
}

const char* Computer::getGPUModel() const
{
	return this->GPUModel;
}

const double Computer::getCPUPower() const
{
	return this->CPUPower;
}

const size_t Computer::getPowerSupply() const
{
	return this->powerSupply;
}

const size_t Computer::getRAM() const
{
	return this->RAM;
}

void Computer::setGPUModel(const char* GPUModel)
{
	if (!GPUModel)
		throw std::runtime_error("NULLPTR!");
	
	this->GPUModel = new char[strlen(GPUModel) + 1];
	strcpy(this->GPUModel, GPUModel);
}

void Computer::setCPUPower(double CPUPower)
{
	if (CPUPower < 0)
		throw std::out_of_range("CPU power must be positive!");
	
	this->CPUPower = CPUPower;
}

void Computer::setPowerSupply(size_t powerSupply)
{
	if (powerSupply < 0)
		throw std::out_of_range("Power supply must be positive!");
	
	this->powerSupply = powerSupply;
}

void Computer::setRAM(size_t RAM)
{
	if (RAM < 0)
		throw std::out_of_range("RAM must be positive!");
	
	this->RAM = RAM;
}

Computer::~Computer() noexcept
{
	free();
}

void Computer::copyFrom(const Computer& other)
{
	this->GPUModel = new char[strlen(other.GPUModel) + 1];
	strcpy(this->GPUModel, other.GPUModel);
	
	this->CPUPower = other.CPUPower;
	this->powerSupply = other.powerSupply;
	this->RAM = other.RAM;
}

void Computer::moveFrom(Computer&& other) noexcept
{
	this->GPUModel = other.GPUModel;
	this->CPUPower = other.CPUPower;
	this->powerSupply = other.powerSupply;
	this->RAM = other.RAM;
	
	other.GPUModel = nullptr;
	other.CPUPower = other.powerSupply = other.RAM = 0;
}

void Computer::free()
{
	delete[] this->GPUModel;
	
	this->GPUModel = nullptr;
	this->CPUPower = this->powerSupply = this->RAM = 0;
}