/**
Specific pattern finder
Uses specific symbols with different meaning
*
*/

#include <iostream>
int myStrLen(const char* str) {
    if (!str)return -1;
    int len = 0;
    while (*str) {
        str++;
        len++;
    }
    return len;
}
bool isValidSymbol(char symbol) {
    return (symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z') || (symbol >= '0' && symbol <= '9') || (symbol==' ');
}
bool isStringValid(const char* str) {
    if (!str)return false;
    while (*str) {
        if (!isValidSymbol(*str))return false;
        str++;
    }
    return true;
}
//declaring a function that gives information about the symbol - is it a digit or not(a letter)
bool isDigit(char symbol) {
    return (symbol >= '0' && symbol <= '9');
}
bool isEmptySpace(char symbol) {
    return (symbol == ' ');
}
bool checkPattern(const char* str, const char* pattern, int lenOfPattern) {
    if (!str || !pattern)return false;
    //we will need a variable to easily access the elements of the pattern string
    //it starts with -1 because we directly change it at the start of the while loop
    int pos = -1;
    while(*str) {
        ++pos;
        if (pos == lenOfPattern)break;
        if (isDigit(*str)) {
            if (pos == 0) {
                if ((*str) != pattern[pos] && pattern[pos] != '*' && pattern[pos] != '%')return false;
            }
            else if ((*str) != pattern[pos] && pattern[pos] != '*' && pattern[pos] != '%' && pattern[pos-1] != '%') {
                return false;
            }
        }
        else if (isEmptySpace(*str)) {
            if ((*str) != pattern[pos] && pattern[pos] != '*') {
                return false;
            }
        }
        else {
            if ((*str) != pattern[pos] && pattern[pos] != '*' && pattern[pos] != '@') {
                return false;
            }
        }
        str++;
     }
    if (pos < lenOfPattern - 1)return false;
    return true;
}
int countPatternAppearances(const char* str, const char* pattern) {
    if (!str || !pattern)return -1;
    int lenOfPattern = myStrLen(pattern);
    int countAppear = 0;
    while (*str) {
        if (checkPattern(str, pattern, lenOfPattern)) {
            countAppear++;
        }
        str++;
    }
    return countAppear;
}
int main()
{
    constexpr size_t MAX_STRING_SIZE = 1024;
    char str[MAX_STRING_SIZE + 1];
    std::cin.getline(str, MAX_STRING_SIZE);
    char pattern[MAX_STRING_SIZE + 1];
    std::cin.getline(pattern, MAX_STRING_SIZE);
    if (myStrLen(str) < myStrLen(pattern)) {
        std::cout << "0";
        return 0;
    }
    if (!isStringValid(str) || pattern == nullptr ) {
        std::cout << "Incorrect input";
        return -1;
    }
    int count = countPatternAppearances(str, pattern);
    if (count == -1) {
        std::cout << "Incorrect input";
        return -1;
    }
    std::cout << count;
}


