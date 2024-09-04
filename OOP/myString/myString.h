#pragma once
#include <iostream>
#include <fstream>
class myString
{
private:
	char* data = nullptr;
	size_t size = 0;
	size_t capacity = 4;
	void resize(size_t newCapacity);
	void free();
	void copyFrom(const myString& other);
	void moveFrom(myString&& other);
public:
	myString();
	myString(const myString& other);
	myString(myString&& other);
	myString(const char* newString);
	myString& operator=(const myString& other);
	myString& operator=(myString&& other);
	~myString();
	const char* getStr() const; //  = c_str function in std::string
	size_t getSize() const;
	void setStr(const char* newStr);
	friend std::ostream& operator<<(std::ostream& os, const myString& str);
	friend std::istream& operator>>(std::istream& is, myString& str);
	bool operator==(const myString& other) const;
	bool operator!=(const myString& other) const;
	myString& operator+=(const myString& other);
	size_t operator~() const; // = getSize()
};

myString operator+(const myString& left, const myString& right);

