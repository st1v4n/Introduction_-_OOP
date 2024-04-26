#include "GroupTicket.h"
const MyString& GroupTicket::getName() const
{
	return Ticket::getName();
}

double GroupTicket::getPrice() const
{
	return Ticket::getPrice();
}

void GroupTicket::setName(const MyString& name)
{
	Ticket::setName(name);
}

void GroupTicket::setPrice(double price)
{
	Ticket::setPrice(price);
}

std::ostream& operator<<(std::ostream& os, const GroupTicket& ticket)
{
	os << "Name of production: " << ticket.getName() << std::endl;
	os << "Price of ticket: " << ticket.getPrice() << std::endl;
	return os;
}

std::istream& operator>>(std::istream& is, GroupTicket& ticket)
{
	MyString name;
	is >> name;
	ticket.setName(name);
	double price;
	is >> price;
	ticket.setPrice(price);
	return is;
}
