#include "Student.h"

Student::Student(const MyString& name, unsigned fn, unsigned course)
{
	setName(name);
	setFn(fn);
	setCourse(course);
}

void Student::setName(const MyString& name)
{
	this->name = name;
}

void Student::setFn(unsigned fn)
{
	if (fn <= 0)throw - 123;
	this->fn = fn;
}

void Student::setCourse(unsigned course)
{
	if (course < 1 || course > 4)throw - 123;
	this->course = course;
}

const MyString& Student::getName() const
{
	return this->name;
}

unsigned Student::getFn() const
{
	return this->fn;
}

unsigned Student::getCourse() const
{
	return this->course;
}
