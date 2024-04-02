/**
*
* Solution to homework assignment 1
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Stivan Nikolaev Aleksandrov
* @idnumber 
* @task 3
*
*/

#include <iostream>
void updateArrayAfterDeletion(char ballColorsRow[], size_t& size, int& position, char& color, int countConsecutive) {
    bool isConsecutiveFinished = false;
    for (int k = position + 1;k < size;k++) {
        if (isConsecutiveFinished) {
            ballColorsRow[k - countConsecutive] = ballColorsRow[k];
        }
        else if (ballColorsRow[k] != color) {
            ballColorsRow[k - countConsecutive] = ballColorsRow[k];
            //when we found a different color
            isConsecutiveFinished = true;
            //when we find different color, there is always a possibility that it makes a new consecutive row
            color = ballColorsRow[k];
            position = k - countConsecutive;
        }
    }
    //size decreases by the number of Consecutive colors that were cut
    size -= countConsecutive;
}
bool isConsecutiveColor(const char ballColorsRow[], size_t size, int position, char color, int& countConsecutive) {
    countConsecutive = 1;
    //counting the left side
    for (int k = position - 1;k >= 0;k--) {
        if (ballColorsRow[k] == color)countConsecutive++;
        else {
            break;
        }
    }
    //counting the right side
    for (int k = position + 1;k < size;k++) {
        if (ballColorsRow[k] == color)countConsecutive++;
        else {
            break;
        }
    }
    return countConsecutive >= 3;
}
void updateArrayAfterShot(char ballColorsRow[], size_t& size, int positionOfAddedElement, char addedBallColor) {
    //when shooting, the size of the array increases by 1 (we add new color to the row)
    ++size;
    //setting the start point to be the last element
    int start = size - 2;
    for (int k = start;k >= positionOfAddedElement;k--) {
        ballColorsRow[k + 1] = ballColorsRow[k];
    }
    ballColorsRow[positionOfAddedElement] = addedBallColor;
}
void shootBalls(char ballColorsRow[], size_t& size, int numberOfShots) {
    int i;
    char c;
    for (int k = 1;k <= numberOfShots;k++) {
        std::cin >> i;
        std::cin >> c;
        if (c < 'a' || c>'z') {
            std::cout << "Incorrect input";
            break;
        }
        if ((i < 0 || i > size - 1) || size == 0)continue;
        int positionOfAddedElement = i + 1;
        updateArrayAfterShot(ballColorsRow, size, positionOfAddedElement, c);
        //declaring a variable that shows the number of consecutive color
        int countConsecutive;
        while (isConsecutiveColor(ballColorsRow, size, positionOfAddedElement, c, countConsecutive)) {
            updateArrayAfterDeletion(ballColorsRow, size, positionOfAddedElement, c, countConsecutive);
            if (size <= 0)break;
        }
    }
}
void outputBallRow(const char ballColorsRow[], size_t size) {
    for (int k = 0;k < size;k++) {
        std::cout << ballColorsRow[k] << " ";
    }
}
int main()
{
    size_t n;
    std::cin >> n;
    if (n <= 0 || n >= 256) {
        std::cout << "Incorrect input";
        return -1;
    }
    //going to declare an array that shows the state of the row at the start and after every single shot
    // that constant is the number of max possible row of balls 
    constexpr size_t SIZE_BALL_ROW = 256 + 128;
    char ballColorsRow[SIZE_BALL_ROW];
    for (int i = 0;i < n;i++) {
        std::cin >> ballColorsRow[i];
        if (ballColorsRow[i] < 'a' || ballColorsRow[i]>'z') {
            std::cout << "Incorrect input";
            return -1;
        }
    }
    int s;
    std::cin >> s;
    if (s < 0 || s>127) {
        std::cout << "Incorrect input";
        return -1;
    }
    shootBalls(ballColorsRow, n, s);
    if (n == 0) {
        std::cout << "-1";
    }
    else {
        outputBallRow(ballColorsRow, n);
    }
}


