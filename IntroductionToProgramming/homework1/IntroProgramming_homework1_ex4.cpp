/**
*
* Solution to homework assignment 1
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Stivan Nikolaev Aleksandrov
* @idnumber 3MI0600301
* @task 4
*
*/


#include <iostream>
const int MIN_MONTH = 1;
const int MAX_MONTH = 12;
const int MAX_YEAR = 2100;
const int MIN_YEAR = 1600;
bool isIntervalValid(int yearStart,int monthStart, int dayStart,int yearEnd,int monthEnd,int dayEnd) {
    if (yearStart > yearEnd || (yearStart == yearEnd && monthStart > monthEnd) || (yearStart == yearEnd && monthStart == monthEnd && dayStart > dayEnd)) {
        return false;
    }
    return true;
}
bool isLeapYear(int year,int month,int day) {
    //checking what calendar was used at that moment
    if (year <= 1916 && month <= 3 && day <= 31) {
        return year % 4 == 0;
    }
    else {
        if (year % 4 == 0) {
            if (year % 400 == 0) {
                return true;
            }
            else if (year % 100 == 0) {
                return false;
            }
            return true;
        }
    }
    return false;
}
int getDaysInMonth(int year, int month,int day) {
    if (month == 2) {
        if (isLeapYear(year,month,day)) {
            return 29;
        }
        else {
            return 28;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    else {
        return 31;
    }

}
void inputDate(int& year, int& month, int& day, bool& isInputValid) {
    std::cin >> year;
    if (year<MIN_YEAR || year>MAX_YEAR) {
        isInputValid = false;
    }
    std::cin >> month;
    if (month<MIN_MONTH || month>MAX_MONTH) {
        isInputValid = false;
    }
    std::cin >> day;
    if (day<1 || day>getDaysInMonth(year,month,day)) {
        isInputValid = false;
    }
    if (year == 1916 && month == 4 && (day >= 1 && day <= 13)) {
        isInputValid = false;
    }
}
void updateDate(int& year, int& month, int& day) {
    while (day > getDaysInMonth(year, month, day)) {
        day = day - getDaysInMonth(year, month, day);
        ++month;
    }
    if (month > MAX_MONTH) {
        month = month - MAX_MONTH;
        ++year;
    }
}
void solveSpecificCasesOfDates(int& year, int& month, int& day,int n, int callComingFrom) {
    // checking which part of the interval called the function
    if (callComingFrom == 1) {
        while (year == 1916 && month == 4 && (day >= 1 && day <= 13)) {
            day += n - 1;
            updateDate(year, month, day);
        }
    }
    else {
        while (year == 1916 && month == 4 && (day >= 1 && day <= 13)) {
            day++;
            updateDate(year, month, day);
        }
    }
}
void outputDate(int year, int month, int day) {
    std::cout << year << "-" << month << "-" << day;
}
void generateDates(int yearStart, int monthStart, int dayStart, int yearEnd, int monthEnd, int dayEnd, int n) {
    //declaring a variable that will help to determine what date we should print
    int checkPosition = 0;
    std::cout << yearStart << "-" << monthStart << "-" << dayStart<<" - ";
    while (true) {
        if (checkPosition % 2 == 0) {
            dayStart += n - 1;
            ++checkPosition;
            updateDate(yearStart, monthStart, dayStart);
            solveSpecificCasesOfDates(yearStart, monthStart, dayStart, n,1);
            if (yearStart > yearEnd || (yearStart == yearEnd && monthStart > monthEnd) || (yearStart == yearEnd && monthStart == monthEnd && dayStart >= dayEnd)) {
                outputDate(yearEnd, monthEnd, dayEnd);
                break;
            }
            outputDate(yearStart, monthStart, dayStart);
            std::cout << std::endl;            
        }
        else {
            dayStart++;
            ++checkPosition;
            updateDate(yearStart, monthStart, dayStart);
            solveSpecificCasesOfDates(yearStart, monthStart, dayStart, n, 2);
            if (yearStart > yearEnd || (yearStart == yearEnd && monthStart > monthEnd) || (yearStart == yearEnd && monthStart == monthEnd && dayStart >= dayEnd)) {
                outputDate(yearEnd, monthEnd, dayEnd);
            }
            else {               
                    outputDate(yearStart, monthStart, dayStart);                   
            }
            std::cout << " - ";
        }
    }
}
int main()
{
    int yearStart, monthStart, dayStart;
    int yearEnd, monthEnd, dayEnd;
    bool isInputValid = true;
    inputDate(yearStart, monthStart, dayStart, isInputValid);
    inputDate(yearEnd, monthEnd, dayEnd, isInputValid);
    int n;
    std::cin >> n;
    if (n < 1 || n >365) {
        std::cout << "Incorrect input";
        return -1;
    }
    if (!isIntervalValid(yearStart,monthStart,dayStart,yearEnd,monthEnd,dayEnd) || !isInputValid) {
        std::cout << "Incorrect input";
        return -1;
    }
    generateDates(yearStart, monthStart, dayStart, yearEnd, monthEnd, dayEnd, n);
}

