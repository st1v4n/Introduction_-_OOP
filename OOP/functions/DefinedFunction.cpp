#include "DefinedFunction.h"

void DefinedFunction::free()
{
	delete[] arr;
	arr = nullptr;
	N = 0;
}

void DefinedFunction::copyFrom(const DefinedFunction& other)
{
	N = other.N;
	arr = new int32_t[N];
	for (int i = 0;i < N;i++) {
		arr[i] = other.arr[i];
	}
}

void DefinedFunction::moveFrom(DefinedFunction&& other)
{
	N = other.N;
	other.N = 0;
	arr = other.arr;
	other.arr = nullptr;
}

DefinedFunction::DefinedFunction(const DefinedFunction& other)
{
	copyFrom(other);
}

DefinedFunction::DefinedFunction(DefinedFunction&& other)
{
	moveFrom(std::move(other));
}

DefinedFunction& DefinedFunction::operator=(const DefinedFunction& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

DefinedFunction& DefinedFunction::operator=(DefinedFunction&& other)
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

DefinedFunction::~DefinedFunction()
{
	free();
}

DefinedFunction::DefinedFunction(const int32_t* arr, size_t N)
{
	this->N = N;
	this->arr = new int32_t[N];
	for (int i = 0;i < N;i++) {
		this->arr[i] = arr[i];
	}
}

bool DefinedFunction::operator()(int32_t x) const
{
	for (int i = 0;i < N;i++) {
		if (arr[i] == x)return true;
	}
	return false;
}
