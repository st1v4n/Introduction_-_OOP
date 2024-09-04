#include "myString.h"
static size_t stringLen(const char* str) {
	if (!str)return -1;
	size_t count = 0;
	while (*str) {
		count++;
		str++;
	}
	return count;
}
static void stringCopy(char* dest, const char* source) {
	if (!dest || !source)return;
	while (*source) {
		(*dest) = (*source);
		dest++;
		source++;
	}
	(*dest) = '\0';
}
static bool areStringsEqual(const char* left, const char* right) {
	if (!left || !right) return false;
	while ((*left) && (*right)) {
		if ((*left) != (*right))return false;
		left++;
		right++;
	}
	return (*left) == (*right);
}
static void stringConcat(char* dest, const char* toAdd) {
	if (!dest || !toAdd)return;
	dest += stringLen(dest);
	stringCopy(dest, toAdd);
}
void myString::resize(size_t newCapacity)
{
	char* newData = new (std::nothrow) char[newCapacity] {'\0'};
	if (!newData)return;
	for (int i = 0;i < size;i++) {
		newData[i] = data[i];
	}
	capacity = newCapacity;
	delete[] data;
	data = newData;
}

void myString::free()
{
	delete[] data;
	size = 0;
	capacity = 4;
}

void myString::copyFrom(const myString& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new (std::nothrow) char[capacity] {'\0'};
	if (!data)return;
	for (int i = 0;i < size;i++) {
		data[i] = other.data[i];
	}
}

void myString::moveFrom(myString&& other)
{
	size = other.size;
	capacity = other.capacity;
	data = other.data;
	other.size = 0;
	other.capacity = 4;
	other.data = nullptr;
}

myString::myString()
{
	size = 0;
	capacity = 4;
	data = new (std::nothrow) char[capacity] {'\0'};
	if (!data)throw std::logic_error("could not create data!");
}

myString::myString(const myString& other)
{
	copyFrom(other);
}

myString::myString(myString&& other)
{
	moveFrom(std::move(other));
}

myString::myString(const char* newString)
{
	size = stringLen(newString);
	if (size > 0) {
		capacity = size * 2;
		data = new (std::nothrow) char[capacity] {'\0'};
		if (!data)throw std::logic_error("could not create data!");
		stringCopy(data, newString);
	}
}

myString& myString::operator=(const myString& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

myString& myString::operator=(myString&& other)
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

myString::~myString()
{
	free();
}

const char* myString::getStr() const
{
	return data;
}

size_t myString::getSize() const
{
	return size;
}

void myString::setStr(const char* newStr)
{
	size = stringLen(newStr);
	if (size > 0) {
		capacity = size * 2;
		delete[] data;
		data = new (std::nothrow) char[capacity] {'\0'};
		if (!data)throw std::logic_error("could not create data!");
		stringCopy(data, newStr);
	}
}

bool myString::operator==(const myString& other) const
{
	return areStringsEqual(this->getStr(), other.getStr());
}

bool myString::operator!=(const myString& other) const
{
	return !((*this) == other);
}

myString& myString::operator+=(const myString& other)
{
	if (this->size + other.size + 1 > this->capacity)resize(2 * (this->size + other.size + 1));
	stringConcat(this->data, other.data);
	return *this;
}

size_t myString::operator~() const
{
	return size;
}

std::ostream& operator<<(std::ostream& os, const myString& str)
{
	os << str.data;
	return os;
}

std::istream& operator>>(std::istream& is, myString& str)
{
	char buff[1024];
	is >> buff;
	str.setStr(buff);
	return is;
}

myString operator+(const myString& left, const myString& right)
{
	myString result(left);
	result += right;
	return result;
}
