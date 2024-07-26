#include "GenericFunction.h"

GenericFunction::GenericFunction(size_t size)
{
	this->size = size;
	points = new Pair<int32_t, int32_t>[size];
}

int32_t GenericFunction::operator()(int32_t x) const
{
	for (int i = 0;i < size;i++) {
		if (points[i].getX() == x) {
			return points[i].getY();
		}
	}
	throw std::logic_error("Point is undefined!");
}

void GenericFunction::setPoint(const Pair<int32_t, int32_t>& newPoint, int index)
{
	if (index >= size)throw std::out_of_range("Invalid index!");
	points[index] = newPoint;
}

void GenericFunction::setPointX(int32_t x, int index)
{
	if (index < 0 || index >= size)return;
	points[index].setX(x);
}

void GenericFunction::setPointY(int32_t y, int index)
{
	if (index < 0 || index >= size)return;
	points[index].setY(y);
}

Pair<int32_t, int32_t> GenericFunction::getPoint(int index) const
{
	if (index >= size)throw std::out_of_range("Invalid index!");
	return points[index];
}

void GenericFunction::free()
{
	delete[] points;
	points = nullptr;
	size = 0;
}

void GenericFunction::copyFrom(const GenericFunction& other)
{
	points = new Pair<int32_t, int32_t>[other.size];
	for (int i = 0;i < other.size;i++) {
		points[i] = other.points[i];
	}
	size = other.size;
}

void GenericFunction::moveFrom(GenericFunction&& other)
{
	points = other.points;
	other.points = nullptr;
	size = other.size;
	other.size = 0;
}

GenericFunction::GenericFunction(const GenericFunction& other)
{
	copyFrom(other);
}

GenericFunction::GenericFunction(GenericFunction&& other)
{
	moveFrom(std::move(other));
}

GenericFunction& GenericFunction::operator=(const GenericFunction& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

GenericFunction& GenericFunction::operator=(GenericFunction&& other)
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

GenericFunction::~GenericFunction()
{
	free();
}
