
#include "NumberSeries.h"

void NumberSeries::copyFrom(const NumberSeries& other)
{
	startNumber = other.startNumber;
	size = other.size;
	func = other.func;
	series = new uint32_t[size];
	for (int i = 0;i < size;i++) {
		series[i] = other.series[i];
	}
}

void NumberSeries::free()
{
	if (series != nullptr) {
		delete[] series;
	}
	series = nullptr;
	startNumber = size = 0;
}

void NumberSeries::setStart(int number)
{
	free();
	this->startNumber = number;
}

int NumberSeries::getStart() const
{
	return startNumber;
}

void NumberSeries::setFunc(int(*func)(int))
{
	free();
	this->func = func;
}

NumberSeries::NumberSeries()
{
	startNumber = size = 0;
	func = nullptr;
	series = nullptr;
}

NumberSeries::NumberSeries(int startNumber, int(*func)(int))
{
	this->startNumber = startNumber;
	this->func = func;
}

NumberSeries::NumberSeries(const NumberSeries& other)
{
	copyFrom(other);
}

NumberSeries& NumberSeries::operator=(const NumberSeries& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

NumberSeries::~NumberSeries()
{
	free();
}

int NumberSeries::generateI(int i)
{
	if (size >= i)return series[i];
	int start = startNumber;
	free();
	size = i + 1;
	startNumber = start;
	series = new uint32_t[size]{ 0 };
	series[0] = startNumber;
	for (int j = 1;j <= i;j++) {
		series[j] = func(series[j - 1]);
	}
	return series[i];
}

void NumberSeries::printSeries() const
{
	for (int i = 0;i < size;i++) {
		std::cout << series[i] << " ";
	}
	std::cout << std::endl;
}

NumberSeries& NumberSeries::operator+=(const NumberSeries& other)
{
	int min = size > other.size ? other.size : size;
	for (int i = 0;i < min;i++) {
		series[i] += other.series[i];
	}
	return *this;
}

NumberSeries& NumberSeries::operator*=(const NumberSeries& other)
{
	int min = size > other.size ? other.size : size;
	for (int i = 0;i < min;i++) {
		series[i] *= other.series[i];
	}
	return *this;
}

std::ostream& operator<<(std::ostream& os, const NumberSeries& series)
{
	for (int i = 0;i < series.size;i++) {
		os << series.series[i] << " ";
	}
	return os;
}
