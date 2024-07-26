
//Homework 3
//that is the main file!
//some of the other files will be hpp, even though they are not template, because otherwise i had to sent 30 files :)
#include "CriteriaFunction.hpp"
#include "GenericFunction.h"
#include "DefinedFunction.h"
#include "Container.hpp"
#include "MaximumFunction.hpp"
#include "MinimumFunction.hpp"
enum class Types {
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR
};
namespace Commands {
    //if you want to stop the program!
    char exit_command[5] = "exit";
}
static bool strcompare(const char* str1, const char* str2) {
    if (!str1 || !str2)return false;
    while ((*str1) && (*str2)) {
        if ((*str1) != (*str2))return false;
        str1++;
        str2++;
    }
    return (*str1) == (*str2);
}
static int32_t strToNumber(const char* str) {
    if (!str)return -1;
    int32_t sign = 1;
    if ((*str) == '-') {
        sign = -1;
        str++;
    }
    int32_t number = 0;
    while (*str) {
        (number *= 10) += (*str) - '0';
        str++;
    }
    return number*sign;
}

static PartialFunction* typeTwo(uint16_t N, std::ifstream& ifs) {
    CriteriaFunction<DefinedFunction> criteriaFunction;
    int32_t* arr = new int32_t[N];
    for (int i = 0;i < N;i++) {
        int32_t number;
        ifs.read((char*)&number, sizeof(int32_t));
        arr[i] = number;
    }
    DefinedFunction definedFunction(arr, N);
    criteriaFunction.setFunction(definedFunction);
    return new CriteriaFunction<DefinedFunction>(criteriaFunction);
}
static PartialFunction* typeOne(uint16_t N, std::ifstream& ifs){
    CriteriaFunction<int32_t(*)(int32_t)> criteriaFunction([](int32_t x) -> int32_t {return x;});
    criteriaFunction.setSize(N);
    for (int i = 1;i <= N;i++) {
        int32_t number;
        ifs.read((char*)&number, sizeof(int32_t));
        criteriaFunction.setDefinedPoint(number, 0, i - 1);
    }
    return new CriteriaFunction<int32_t(*)(int32_t)>(criteriaFunction);
}
static PartialFunction* typeZero(uint16_t N, std::ifstream& ifs) {
    GenericFunction newFunction(N);
    CriteriaFunction<GenericFunction> criteriaFunction;
    for (int i = 1;i <= N;i++) {
        int32_t x =0;
        ifs.read((char*)&x, sizeof(int32_t));
        newFunction.setPointX(x, i - 1);
    }
    for (int i = 1;i <= N;i++) {
        int32_t y=0;
        ifs.read((char*)&y, sizeof(int32_t));
        newFunction.setPointY(y, i - 1);
    }
    criteriaFunction.setFunction(newFunction);
    return new CriteriaFunction<GenericFunction>(criteriaFunction);
}
void generateInInterval(const PartialFunction* function) {
    int32_t a, b;
    std::cin >> a >> b;
    for (int32_t i = a;i <= b;i++) {
        try {
            (*function)(i).printAsFunction();
        }
        catch (std::exception& ex) {
            //the points is undefined
        }
    }
}
void generateSpecificPoints(const PartialFunction* function) {
    while (true) {
        char buff[10];
        std::cin >> buff;
        if (strcompare(buff, Commands::exit_command))return;
        int32_t number = strToNumber(buff);
        try {
            (*function)(number).printAsFunction();
        }
        catch (std::exception& ex) {
            std::cout << "x = " << number << ":";
            std::cout << ex.what()<<'\n';
        }
    }
}
void proceed(const PartialFunction* function) {
    std::cout << "Everything loaded!"<<'\n';
    std::cout << "Make a choice:" << "\n";
    std::cout << "1: Interval [a ; b]"<<"\n";
    std::cout << "2: Generate your own points" << '\n';
    std::cout << "Type the choosen number (1 or 2): ";
    int16_t number = 0;
    std::cin >> number;
    switch (number) {
    case 1: generateInInterval(function);return;
    case 2: generateSpecificPoints(function);return;
    default: std::cout << "Unknown type!";return;
    }
}
void generateFileName(char* buff, std::ifstream& ifs) {
    if (!buff)return;
    while (true) {
        ifs.read((char*)&(*buff), sizeof(char));
        if (!(*buff))return;
        buff++;
    }
}
void setFunction(std::ifstream& ifs, PartialFunction*& function, int16_t T, int16_t N) {
    switch (T) {
    case (int)Types::ZERO: {
        function = typeZero(N, ifs);
        return;
    }
    case (int)Types::ONE: {
        function = typeOne(N, ifs);
        return;
    }
    case (int)Types::TWO: {
        function = typeTwo(N, ifs);
        return;
    }
    case (int)Types::THREE: {
        try {
            if (N == 0)return;
            Container functions(N);
            for (size_t i = 0; i < N; i++) {
                char buff[100]{ '\0' };
                generateFileName(buff, ifs);
                std::ifstream newIfs(buff, std::ios::binary);
                if (!newIfs.is_open()) {
                    std::cout << "Cannot open the file!";
                    return;
                }
                int16_t newN, newT;
                newIfs.read((char*)&newN, sizeof(int16_t));
                if (newN < 0 || newN > 32) {
                    std::cout << "Invalid N!";
                    throw "Error";
                }
                newIfs.read((char*)&newT, sizeof(int16_t));
                PartialFunction* newFunction = nullptr;
                setFunction(newIfs, newFunction, newT, newN);
                functions.add(newFunction, i);
                delete newFunction;
                if (i == N - 1) {
                    function = new MaximumFunction(functions);
                    return;
                }
            }
        }
        catch (...) {
            std::cout << "Unexpected Error!";
            return;
        }
        return;
    }
    case (int)Types::FOUR: {
        try {
            if (N == 0)return;
            Container functions(N);
            for (size_t i = 0; i < N; i++) {
                char buff[100]{ '\0' };
                generateFileName(buff, ifs);
                std::ifstream newIfs(buff, std::ios::binary);
                if (!newIfs.is_open()) {
                    std::cout << "Cannot open the file!";
                    return;
                }
                int16_t newN, newT;
                newIfs.read((char*)&newN, sizeof(int16_t));
                if (newN < 0 || newN > 32) {
                    std::cout << "Invalid N!";
                    throw "Error";
                }
                newIfs.read((char*)&newT, sizeof(int16_t));
                PartialFunction* newFunction = nullptr;
                setFunction(newIfs, newFunction, newT, newN);
                functions.add(newFunction, i);
                delete newFunction;
                if (i == N - 1) {
                    function = new MinimumFunction(functions);
                    return;
                }
            }
        }
        catch (...) {
            std::cout << "Unexpected Error!";
            return;
        }
        return;
    }
    default: throw std::out_of_range("Invalid T");
    }
}
int main()
{
    char fileName[100] = "func.dat";
    std::ifstream ifs(fileName, std::ios::binary);
    if (!ifs.is_open()) {
        return -1;
    }
    int16_t N, T;
    ifs.read((char*)&N, sizeof(int16_t));
    ifs.read((char*)&T, sizeof(int16_t));
    if (N < 0 || N > 32) {
        std::cout << "Invalid N";
        return -1;
    }
    PartialFunction* function = nullptr;
    try {
        setFunction(ifs, function, T, N);
        proceed(function);
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << '\n';
    }
    delete function;
}


