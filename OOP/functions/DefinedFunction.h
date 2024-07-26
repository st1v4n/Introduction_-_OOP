#pragma once
#include <iostream>
//another object that acts as a function
//used for functions that have a value of either 1 or 0 under specific scenario
class DefinedFunction
{
private:
	int32_t* arr = nullptr;;
	size_t N = 0;
	void free();
	void copyFrom(const DefinedFunction& other);
	void moveFrom(DefinedFunction&& other);
public:
	DefinedFunction() = default;
	DefinedFunction(const DefinedFunction& other);
	DefinedFunction(DefinedFunction&& other);
	DefinedFunction& operator=(const DefinedFunction& other);
	DefinedFunction& operator=(DefinedFunction&& other);
	~DefinedFunction();
	DefinedFunction(const int32_t* arr, size_t N);
	bool operator()(int32_t x) const;
};

