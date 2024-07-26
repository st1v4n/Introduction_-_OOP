#pragma once
#include "PartialFunction.h"
class Container {
private:
	PartialFunction** functions = nullptr;
	size_t size = 0;
	void free();
	void copyFrom(const Container& other);
	void moveFrom(Container&& other);
public:
	Container() = default;
	~Container();
	Container(const Container& other);
	Container(Container&& other);
	Container& operator=(const Container& other);
	Container& operator=(Container&& other);
	Container(size_t size);
	void add(const PartialFunction* function, int index);
	bool isFunctionDefined(int index, int32_t x) const;
	size_t getSize() const;
	const PartialFunction* getFunction(int index) const;
};

inline void Container::free()
{
	for (int i = 0;i < size;i++) {
		delete functions[i];
	}
	delete[] functions;
}


inline void Container::copyFrom(const Container& other)
{
	size = other.size;
	functions = new PartialFunction*[size];
	for (int i = 0;i < size;i++) {
		functions[i] = other.functions[i]->clone();
	}
}

inline void Container::moveFrom(Container&& other)
{
	size = other.size;
	other.size = 0;
	functions = other.functions;
	other.functions = nullptr;
}

inline Container::~Container()
{
	free();
}

inline Container::Container(const Container& other)
{
	copyFrom(other);
}

inline Container::Container(Container&& other)
{
	moveFrom(std::move(other));
}

inline Container& Container::operator=(const Container& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

inline Container& Container::operator=(Container&& other)
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

inline Container::Container(size_t size)
{
	functions = new PartialFunction*[size];
	this->size = size;
}

inline void Container::add(const PartialFunction* function, int index)
{
	if (index >= size)return;
	functions[index] = function->clone();
}

inline bool Container::isFunctionDefined(int index, int32_t x) const
{
	if (index >= size)throw std::out_of_range("Invalid Index!");
	return functions[index]->isDefined(x);
}

inline size_t Container::getSize() const
{
	return size;
}

inline const PartialFunction* Container::getFunction(int index) const
{
	if (index >= size)throw std::out_of_range("Invalid Index!");
	return functions[index];
}
