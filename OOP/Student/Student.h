#pragma once
#include "MyString.h"
class Student
{
	MyString name = "UNKNOWN";
	unsigned fn = 0;
	unsigned course = 0;

public:
	Student() = default;
	Student(const MyString& name, unsigned fn, unsigned course);
	void setName(const MyString& name);
	void setFn(unsigned fn);
	void setCourse(unsigned course);
	const MyString& getName()const;
	unsigned getFn()const;
	unsigned getCourse()const;
};

