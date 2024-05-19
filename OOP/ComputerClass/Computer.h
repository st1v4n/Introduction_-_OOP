#pragma once
#include <iostream>
#pragma warning(disable : 4996)
class Computer
{
private:
	void free();
	void copyFrom(const Computer& other);
	void moveFrom(Computer&& other);
protected:
	double cpuPower = 0;
	char* gpuType = nullptr;
	int voltagePower = 0;
	int RAM = 0;

public:
	Computer() = default;
	~Computer();
	Computer(const Computer& other);
	Computer(Computer&& other);
	Computer& operator=(const Computer& other);
	Computer& operator=(Computer&& other);
	void setCpuPower(double cpuPower) {
		if (cpuPower < 0)throw - 123;
		this->cpuPower = cpuPower;
	}
	void setGpuType(const char* gpuType) {
		if (gpuType == nullptr)throw - 123;
		this->gpuType = new char[strlen(gpuType) + 1];
		strcpy(this->gpuType, gpuType);
	}
	void setVoltage(int voltagePower) {
		if (voltagePower < 0)throw - 123;
		this->voltagePower = voltagePower;
	}
	void setRam(int RAM) {
		if (RAM < 0 || RAM % 2 != 0)throw - 123;
		this->RAM = RAM;
	}
	virtual void printType() const = 0;
	virtual void printRemoteDevices() const = 0;
};

class PC :public Computer {
	void printType() const override {
		std::cout << "->PC<-" << std::endl;
	}
	void printRemoteDevices() const override {
		std::cout << " Mouse, Keyboard, Microphone, Headphones"<<std::endl;
	}
};
class Laptop :public Computer {
	void printType() const override {
		std::cout << "->Laptop<-" << std::endl;
	}
	void printRemoteDevices() const override {
		std::cout << " MousePad, Keyboard, Monitor" << std::endl;
	}
};
class GamingConsole :public Computer {
	void printType() const override {
		std::cout << "->Gaming console<-" << std::endl;
	}
	void printRemoteDevices() const override {
		std::cout << " JoyStick, Monitor" << std::endl;
	}
};

