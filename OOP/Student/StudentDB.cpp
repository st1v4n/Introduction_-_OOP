#include "StudentDB.h"

void StudentDB::free()
{
	delete[] db;
	size = 0;
	capacity = 4;
}

void StudentDB::copyFrom(const StudentDB& other)
{

	this->db = new Student[other.capacity];
	for (int i = 0; i < size; i++) {
		db[i] = other.db[i];
	}
	size = other.size;
	capacity = other.capacity;
}

void StudentDB::moveFrom(StudentDB&& other)
{
	db = other.db;
	other.db = nullptr;
	size = other.size;
	other.size = 0;
	capacity = other.capacity;
	other.capacity = 4;
}

void StudentDB::resize()
{
	Student* copy = new Student[capacity];
	for (int i = 0; i < size; i++) {
		copy[i] = db[i];
	}
	delete[] db;
	capacity = size * 2;
	db = new Student[capacity];
	for (int i = 0; i < size; i++) {
		db[i] = copy[i];
	}
	delete[] copy;
}

StudentDB::~StudentDB()
{
	free();
}

StudentDB::StudentDB(const StudentDB& other)
{
	copyFrom(other);
}

StudentDB::StudentDB(StudentDB&& other)
{
	moveFrom(std::move(other));
}

StudentDB& StudentDB::operator=(const StudentDB& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

StudentDB& StudentDB::operator=(StudentDB&& other)
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

size_t StudentDB::getSize() const
{
	return size;
}

void StudentDB::add(const Student& newStudent)
{
	if (size >= capacity)resize();
	if (size == 0) {
		db = new Student[capacity];
	}
	db[size] = newStudent;
	size++;
}

void StudentDB::removeByFn(unsigned fn)
{
	for (int i = 0; i < size; i++) {
		if (db[i].getFn() == fn) {
			db[i].setName("<REMOVED>");
			db[i].setFn(0);
			db[i].setCourse(1);
		}
	}
}

std::ostream& operator<<(std::ostream& os, const StudentDB& database)
{
	for (int i = 0; i < database.size; i++) {
		os << "Informatin about Student " << i + 1 <<": " ;
		os << "Name: " << database.db[i].getName() << " ";
		os << "FN: " << database.db[i].getFn() << " ";
		os << "Course: " << database.db[i].getCourse() << " ";
		os << '\n';
	}
	return os;
}
