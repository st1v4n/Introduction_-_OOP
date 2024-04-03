#pragma once
#include <iostream>
#include <fstream>
class NumberSeries {
private:
	int startNumber = 0;
	int (*func)(int);
	int size = 0;
	uint32_t* series;
	void copyFrom(const NumberSeries& other);
	void free();
public:
	void setStart(int number);
	int getStart() const;
	void setFunc(int(*func)(int));
	NumberSeries();
	NumberSeries(int startNumber, int (*func)(int));
	NumberSeries(const NumberSeries& other);
	NumberSeries& operator=(const NumberSeries& other);
	~NumberSeries();
    int generateI(int i);
	void printSeries() const;
	NumberSeries& operator+=(const NumberSeries& other);
	NumberSeries& operator*=(const NumberSeries& other);
	friend std::ostream& operator<<(std::ostream& os, const NumberSeries& series);
};
