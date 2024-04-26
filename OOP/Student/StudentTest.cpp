

#include <iostream>
#include "StudentDB.h"
int main()
{
    StudentDB data;
    Student s1("ivan", 330, 2);
    Student s4("rangel", 491, 3);
    data.add(s1);
    data.add(s4);
    std::cout << data;
}

