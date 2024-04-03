#include <iostream>
#include "Multiset.h"
int main() {
	Multiset set(32);
	Multiset set2(57);
	set2.add(16);
	set2.add(18);
	set2.add(16);
	set2.add(7);
	set2.add(17);
	set2.add(17);
	set.add(7);
	set.add(9);
	set.add(7);
	set.add(17);
	set.add(7);
	set.add(7);
	set.remove(8);
	set.remove(7);
	set.add(56);
	set |= set2;
	set.print();
}