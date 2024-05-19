#include "Computer.h"

void Computer::free()
{
	delete[] gpuType;
	double cpuPower = 0;
	char* gpuType = nullptr;
	int voltagePower = 0;
	int RAM = 0;
}

void Computer::copyFrom(const Computer& other)
{
	this->cpuPower = other.cpuPower;
	this->voltagePower = other.voltagePower;
	this->RAM = other.RAM;
	this->gpuType = new char[strlen(other.gpuType) + 1];
	strcpy(this->gpuType, other.gpuType);
}

void Computer::moveFrom(Computer&& other)
{
	this->cpuPower = other.cpuPower;
	other.cpuPower = 0;
	this->voltagePower = other.voltagePower;
	other.voltagePower = 0;
	this->RAM = other.RAM;
	other.RAM = 0;
	this->gpuType = other.gpuType;
	other.gpuType = nullptr;
}

Computer::~Computer()
{
	free();
}

Computer::Computer(const Computer& other)
{
	copyFrom(other);
}

Computer::Computer(Computer&& other)
{
	moveFrom(std::move(other));
}

Computer& Computer::operator=(const Computer& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Computer& Computer::operator=(Computer&& other)
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

