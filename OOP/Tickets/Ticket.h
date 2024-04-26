#pragma once
#include "MyString.cpp"

class Ticket {
	MyString name = "UNKNOWN";
	double price = 0;
public:
	Ticket() = default;
	Ticket(const MyString& name, double price);
	double getPrice() const;
	const MyString& getName() const;
	void setPrice(double price);
	void setName(const MyString& name);
};
