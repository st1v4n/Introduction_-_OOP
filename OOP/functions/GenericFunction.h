#pragma once
#include "Pair.hpp"

//this class is not mentioned in the task, but i created it as a wrapper class for the array of Pairs (we will call them points)
//objects of this class act as functions and are convinient to use for the template classes mentioned in the task 
class GenericFunction{
private:
	Pair<int32_t, int32_t>* points = nullptr;
	size_t size = 0;
	void free();
	void copyFrom(const GenericFunction& other);
	void moveFrom(GenericFunction&& other);
public:
	GenericFunction() = default;
	GenericFunction(const GenericFunction& other);
	GenericFunction(GenericFunction&& other);
	GenericFunction& operator=(const GenericFunction& other);
	GenericFunction& operator=(GenericFunction&& other);
	~GenericFunction();
	GenericFunction(size_t size);
	int32_t operator()(int32_t x) const;
	void setPoint(const Pair<int32_t, int32_t>& newPoint, int index);
	void setPointX(int32_t x, int index);
	void setPointY(int32_t y, int index);
	Pair<int32_t, int32_t> getPoint(int index) const;
};

