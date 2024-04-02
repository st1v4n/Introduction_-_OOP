/**
*
* Solution to homework assignment 1
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Stivan Nikolaev Aleksandrov
* @idnumber 3MI0600301
* @task 1
*
*/

#include <iostream>
int countDividers(int number) {
    int count = 0;
    for (int i = 1;i <= number;i++) {
        if (number % i == 0) {
            count++;
        }
    }
    return count;
}
void findY(int x, int n, int k, int& countPairs) {
    for (int y = x;y <= n;y++) {
        if (k * countDividers(x) * countDividers(y) == x * y) {
            countPairs++;
        }
    }
}
int countOfXYPairs(int n, int k) {
    int countPairs = 0;
    for (int x = 1;x <= n;x++) {
        findY(x, n, k, countPairs);
    }
    return countPairs;
}
int main()
{
    int n, k;
    std::cin >> n >> k;
    if (n < 1 || k < 1) {
        std::cout << "Incorrect input";
        return -1;
    }
    std::cout << countOfXYPairs(n, k);
}

