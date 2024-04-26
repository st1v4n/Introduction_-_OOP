#include "StudentTicket.h"

const MyString& StudentTicket::getName() const
{
	return Ticket::getName();
}

double StudentTicket::getPrice() const
{
	return Ticket::getPrice();
}

void StudentTicket::setName(const MyString& name)
{
	Ticket::setName(name);
}

void StudentTicket::setPrice(double price)
{
	Ticket::setPrice(price);
}

std::ostream& operator<<(std::ostream& os, const StudentTicket& ticket)
{
	os << "Name of production: " << ticket.getName() << std::endl;
	os << "Price of ticket: " << ticket.getPrice() << std::endl;
	return os;
}

std::istream& operator>>(std::istream& is, StudentTicket& ticket)
{
	MyString name;
	is >> name;
	ticket.setName(name);
	double price;
	is >> price;
	ticket.setPrice(price);
	return is;
}
