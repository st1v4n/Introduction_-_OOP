#pragma once
#include "Student.h"
class StudentDB
{
private:
	Student* db = nullptr;
	size_t size = 0;
	size_t capacity = 4;
	void free();
	void copyFrom(const StudentDB& other);
	void moveFrom(StudentDB&& other);
	void resize();
public:
	StudentDB() = default;
	~StudentDB();
	StudentDB(const StudentDB& other);
	StudentDB(StudentDB&& other);
	StudentDB& operator=(const StudentDB& other);
	StudentDB& operator=(StudentDB&& other);
	size_t getSize()const;
	friend std::ostream& operator<<(std::ostream& os, const StudentDB& database);
	void add(const Student& newStudent);
	void removeByFn(unsigned fn);
};

