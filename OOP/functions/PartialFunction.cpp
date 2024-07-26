#include "PartialFunction.h"

void PartialFunction::free()
{
	delete[] defined_points;
	defined_points = nullptr;
	size = 0;
}

void PartialFunction::copyFrom(const PartialFunction& other)
{
	size = other.size;
	defined_points = new Pair<int32_t, bool>[size];
	for (int i = 0;i < size;i++) {
		defined_points[i] = other.defined_points[i];
	}
}

void PartialFunction::moveFrom(PartialFunction&& other)
{
	size = other.size;
	other.size = 0;
	defined_points = other.defined_points;
	other.defined_points = nullptr;
}

PartialFunction::PartialFunction(const PartialFunction& other)
{
	copyFrom(other);
}

PartialFunction::PartialFunction(PartialFunction&& other)
{
	moveFrom(std::move(other));
}

PartialFunction& PartialFunction::operator=(const PartialFunction& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

PartialFunction& PartialFunction::operator=(PartialFunction&& other)
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

PartialFunction::~PartialFunction()
{
	free();
}

void PartialFunction::setDefinedPointByX(int32_t x, bool isDefined)
{
	for (int i = 0;i < size;i++) {
		if (defined_points[i].getX() == x) {
			defined_points[i].setY(isDefined);
		}
	}
}

void PartialFunction::setDefinedPointByIndex(int index, bool isDefined)
{
	if (index < 0 || index >=size)return;
	defined_points[index].setY(isDefined);
}

void PartialFunction::setSize(size_t newSize)
{
	if (newSize < 0)return;
	size = newSize;
	delete[] defined_points;
	defined_points = new Pair<int32_t, bool>[size];
}

void PartialFunction::setDefinedPoint(int32_t x, bool y, int index)
{
	if (index < 0 || index >= size)return;
	defined_points[index].setX(x);
	defined_points[index].setY(y);
}
