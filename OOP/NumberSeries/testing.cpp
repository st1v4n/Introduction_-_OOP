#include <iostream>
#include "NumberSeries.h"
int func(int number) {
	return number * 2 - 1;
}
int main() {
	NumberSeries series(2,func);
	series.generateI(7);
	std::cout << series.generateI(6)<<std::endl;
	series.printSeries();
	NumberSeries series2(3, func);
	series2.generateI(5);
	std::cout<<(series += series2);
	
}