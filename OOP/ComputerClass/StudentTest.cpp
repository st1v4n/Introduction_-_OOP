
#include <iostream>
#include "Computer.h"
static void printInfo(const Computer* computer) {
	computer->printType();
	computer->printRemoteDevices();
}
int main()
{
	Laptop lap;
	printInfo(&lap);
}

