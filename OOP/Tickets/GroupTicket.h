#pragma once
#include "Ticket.h"
class GroupTicket : public Ticket
{
public:
	GroupTicket(const MyString& name, double price) : Ticket(name, price * 0.8) {};
	const MyString& getName() const;
	double getPrice() const;
	void setName(const MyString& name);
	void setPrice(double price);
	friend std::ostream& operator<<(std::ostream& os, const GroupTicket& ticket);
	friend std::istream& operator>>(std::istream& is, GroupTicket& ticket);
};

