/**
*
Bit manipulation task
*/

#include <iostream>
//because char is 8-bit, we need the first 4 bits, so we will shift 4 positions
const int SHIFT_CHAR = 4;
int myStrLen(const char* str) {
    if (!str)return -1;
    int len = 0;
    while (*str) {
        str++;
        len++;
    }
    return len;
}
void inputInResultStr(char* str,int& position,char symbol) {
    if (!str)return;
    str[position] = symbol;
    position++;
}
// we need to know which part of the symbol we need to code - the first or the second 4 bits
void shiftLeftSymbol(char& symbol, int positions) {
    symbol <<= positions;
}
void shiftRightSymbol(char& symbol, int positions) {
    symbol >>= positions;
}
void code(char symbol, char& result) {
    char helpCode;
    //We have 4 valuable bits at the start, so we need to start shifting by 3 
    int shift = 3;
    result = '\0';
    char one = '1' - '0';
    for (int i = shift;i >= 0;i--) {
        helpCode = symbol;
        shiftLeftSymbol(one, i);
        helpCode = helpCode & one;
        shiftRightSymbol(helpCode, i);
        helpCode++;
        shiftLeftSymbol(helpCode, 2*i);
        result = result | helpCode;
        one = '1' - '0';
    }
}
char codeSymbol(char symbol, bool part) {
    char codedSymbol;
    if (part) {
        shiftRightSymbol(symbol, SHIFT_CHAR);
        code(symbol, codedSymbol);
    }
    else {
        shiftLeftSymbol(symbol, SHIFT_CHAR);
        shiftRightSymbol(symbol, SHIFT_CHAR);
        code(symbol, codedSymbol);
    }
    return codedSymbol;
}
char* codeString(const char* str, int len) {
    if (!str)return nullptr;
    char* result = new char[(2 * len) + 1];
    result[2 * len] = '\0';
    int count = 0;
    char symbol;
    while (*str) {
        symbol=codeSymbol((*str), 1);
        inputInResultStr(result, count, symbol);
        symbol=codeSymbol((*str), 0);
        inputInResultStr(result, count, symbol);
        str++;
    }
    return result;
}
int main()
{
    // including the \0 symbol at the end
    constexpr size_t MAX_SIZE = 65; 
    char str[MAX_SIZE];
    std::cin >> str;
    int lenOfStr = myStrLen(str);
    if (lenOfStr < 1) {
        std::cout << "Incorrect input";
        return -1;
    }
    char* codedString = codeString(str,lenOfStr);
    if (!codedString) {
        std::cout << "Incorrect input";
        return -1;
    }
    std::cout << codedString;
    delete[] codedString;
}


