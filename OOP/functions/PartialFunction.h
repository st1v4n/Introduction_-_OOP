#pragma once
#include <iostream>
#include <fstream>
#include "Pair.hpp"
class PartialFunction
{
private:
	void free();
	void copyFrom(const PartialFunction& other);
	void moveFrom(PartialFunction&& other);
protected:
	//protected because we want to have access after inheritance
	//we don't know the maximum value for x from the files and we cannot do bitset
	// here we will save all the points that were in the files- if they were defined, the value of y will be 1, else it will be 0
	Pair<int32_t, bool>* defined_points = nullptr;
	size_t size = 0;
public:
	PartialFunction() = default;
	PartialFunction(const PartialFunction& other);
	PartialFunction(PartialFunction&& other);
	PartialFunction& operator=(const PartialFunction& other);
	PartialFunction& operator=(PartialFunction&& other);
	virtual ~PartialFunction();
	virtual Pair<int32_t, int32_t> operator()(int32_t x) const = 0;
	virtual bool isDefined(int32_t x) const = 0;
	virtual PartialFunction* clone() const = 0;
	void setDefinedPointByX(int32_t x, bool isDefined);
	void setDefinedPointByIndex(int index, bool isDefined);
	void setSize(size_t newSize);
	void setDefinedPoint(int32_t x, bool y, int index);
};



