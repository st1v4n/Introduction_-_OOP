#include "Ticket.h"

Ticket::Ticket(const MyString& name, double price)
{
	setName(name);
	setPrice(price);
}

double Ticket::getPrice() const
{
	return this->price;
}

const MyString& Ticket::getName() const
{
	return this->name;
}

void Ticket::setPrice(double price)
{
	if (price < 0.0001)throw - 123;
	this->price = price;
}

void Ticket::setName(const MyString& name)
{
	this->name = name;
}
