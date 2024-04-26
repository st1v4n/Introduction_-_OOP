#pragma once
#include "Ticket.h"
#include <fstream>

class StudentTicket : public Ticket {
public:
	StudentTicket(const MyString& name, double price) : Ticket(name, price * 0.5) {};
	const MyString& getName() const;
	double getPrice() const;
	void setName(const MyString& name);
	void setPrice(double price);
	friend std::ostream& operator<<(std::ostream& os, const StudentTicket& ticket);
	friend std::istream& operator>>(std::istream& is, StudentTicket& ticket);
};