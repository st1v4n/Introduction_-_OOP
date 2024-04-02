/**
*
* Solution to homework assignment 1
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Stivan Nikolaev Aleksandrov
* @idnumber 
* @task 2
*
*/
#include <iostream>
void sortAnswers(int array[], size_t size) {
	//sorting the answers of the people
	int maxIndex = 0;
	int max = array[0];
	for (int i = 0;i < size;i++) {
		if (array[i] > max) {
			max = array[i];
			maxIndex = i;
		}
		if (i == size - 1) {
			int p = array[size - 1];
			array[size - 1] = array[maxIndex];
			array[maxIndex] = p;
			max = array[0];
			maxIndex = 0;
			size--;
			i = -1;
		}
	}
}
bool isNewAnswer(const int array[], size_t size,int position,int& countSameAnswers) {
	if (array[position] == array[position - 1]) {
		countSameAnswers++;
		return countSameAnswers > array[position];
	}
	return true;
}
int countMinimalPopulation(const int array[], size_t size) {
	int countPopulation = 0;
	//a variable that will help in counting the answers that were the same 
	int countSameAnswers = 0;
	for (int i = 0;i < size;i++) {
		//checking if there is the same answer a few times in a row, which makes i>=countPopulation variable
		//checking if the current hair style is New (no person has had it yet), which means that it count towards the possible population
		if (isNewAnswer(array, size, i,countSameAnswers)) {
			countSameAnswers = 0;
			countPopulation += array[i] + 1; // increasing the variable with the answer + 1 (the answer + the person that gave it)
		}
	}
	return countPopulation;
}
int main()
{
	int n;
	std::cin >> n;
	if (n < 1 || n>1000) {
		std::cout << "Incorrect input";
		return -1;
	}
	constexpr size_t SIZE_ARRAY = 1000;
	int array[SIZE_ARRAY];
	//input elements of array (up to n)
	for (int i = 0;i < n;i++) {
		std::cin >> array[i];
		if (array[i] < 0 || array[i]>1000) {
			std::cout << "Incorrect input";
			return -1;
		}
	}
	sortAnswers(array, n);
	std::cout << countMinimalPopulation(array, n);
}


