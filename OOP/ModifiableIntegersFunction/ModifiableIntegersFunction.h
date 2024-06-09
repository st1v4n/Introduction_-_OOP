#pragma once
#include <iostream>
#include <fstream>
namespace INT16_FUNCTION_CONSTANTS {
	const int MAX_NUMBER = INT16_MAX;
	const int MIN_NUMBER = INT16_MIN;
	const int8_t MAX_BITS = 8;
	constexpr size_t MAX_SIZE = UINT16_MAX+1;
	constexpr size_t MAX_BUCKET_SIZE = MAX_SIZE / MAX_BITS;
	const size_t CAPACITY_TO_SIZE = 2;
	const size_t INTERVAL_LENGTH = 20;
}
using namespace INT16_FUNCTION_CONSTANTS;
enum class FUNCTION_EXEPTIONS {
	NULLPTR_EXCEPTION=0,
	INVALID_VALUE=1,
	UNDEFINED_EXCEPTION=2
};
static int16_t default_function(int16_t x) {
	return x;
}
static void EXCEPTION_HANDLE(int exceptionCode);
//we will have a struct called ModifiedPoints, where will will store the value of points that are specifically modified by the user
struct ModifiedPoints {
	int16_t x=0;
	int16_t modifiedY=0;
};
//in the program we will often use the cast (uint16_t)x, because there could be some negative numbers and we want our array to function properly
//this way the array will store the numbers in the following order : 0 - (positiveNumbers) - (negativeNumbers), becuse when we cast to uint16_t
// the first bit is not the sign anymore and it contributes as +2^15 to the overall number
class ModifiableIntegersFunction {
private:
	
	int16_t(*function) (int16_t) = default_function;
	ModifiedPoints* modified_points = nullptr;
	size_t size = 0;
	size_t capacity = 4;
	//we create buckets which will be used to determine whether the function is UNDEFINED in specific x
	uint8_t undefined_buckets[MAX_BUCKET_SIZE] = { 0 };
	//we create buckets which will be used to determite whether the function value at a specific x was modified
	uint8_t is_modified_buckets[MAX_BUCKET_SIZE] = { 0 };
	// all the bucket and array functions use unsigned int16 as parametres in order to not allow negative numbers as array index
	// when we give int16_t as an argument, they cast it to uint16_t, which means that the first bit is not the sign anymore
	// it is refered as +2^15
	int getBucketIndex(uint16_t x) const;
	int getBitIndex(uint16_t x) const;
	void setBit(uint8_t& bucket, int bitIndex, uint8_t bit);
	bool getBit(uint8_t bucket, int bitIndex)const;
	bool isModified(uint16_t x) const;
	bool isDefined(uint16_t x) const;
	void free();
	void copyFrom(const ModifiableIntegersFunction& other);
	void moveFrom(ModifiableIntegersFunction&& other);
	void resize();
	void setModified(uint16_t x);
	int16_t findValue(int16_t x)const;
	void setFunctionalValue(int16_t x, int16_t& y)const;
public:
	ModifiableIntegersFunction() = default;
	ModifiableIntegersFunction(int16_t(*func) (int16_t));
	ModifiableIntegersFunction(const ModifiableIntegersFunction& other);
	ModifiableIntegersFunction(ModifiableIntegersFunction&& other) noexcept;
	ModifiableIntegersFunction& operator=(const ModifiableIntegersFunction& other);
	ModifiableIntegersFunction& operator=(ModifiableIntegersFunction&& other) noexcept;
	~ModifiableIntegersFunction();
	void setFunction(int16_t(*func)(int16_t));
	void setSpecificValue(int16_t x, int16_t y);
	void setUndefined(int16_t x);
	//we will have two ways of getting the function value at a x -> getValue function and operator()
	int16_t getValue(int16_t x) const;
	//overloading the operator() in order to make the function look like a mathematical function
	//this way you can now use something like std::cout<<f(3) , it returns int16_t value
	// you can also use something like std::cout<< f(5) + g(2) , because both return int16_t values and can be summed
	//we will define operator+ later, which will give a result = f+g function containing all the result(x) values which will be result(x) = f(x) + g(x) for all x that are defined
	int16_t operator()(int16_t x) const;
	// operator+ creates a new function called result, which is f+g and result(x) = f(x) + g(x);
	friend ModifiableIntegersFunction operator+(const ModifiableIntegersFunction& f, const ModifiableIntegersFunction& g);
	friend ModifiableIntegersFunction operator-(const ModifiableIntegersFunction& f, const ModifiableIntegersFunction& g);
	//operator[] will be used for composition of functions
	//it will return both int16_t value
	//or set a function as a composition of many other functions
	int16_t operator[](int16_t x)const;
	ModifiableIntegersFunction& operator[](const ModifiableIntegersFunction& other);
	//comparison operators 
	bool operator>(const ModifiableIntegersFunction& other)const;
	bool operator<(const ModifiableIntegersFunction& other)const;
	bool operator==(const ModifiableIntegersFunction& other)const;
	bool operator!=(const ModifiableIntegersFunction& other)const;
	//are parallel
	friend bool operator||(const ModifiableIntegersFunction& f, const ModifiableIntegersFunction& g);
	// the opposite function
	friend ModifiableIntegersFunction operator~(const ModifiableIntegersFunction& f);
	bool isInjective()const;
	bool isSurection()const;
	bool isBijection()const;
	void saveToBinary(std::ofstream& ofs)const;
	void readFromBinary(std::ifstream& ifs);
	void drawFunctionInInterval(std::ostream& os, int16_t xStart, int16_t xEnd, int16_t yStart, int16_t yEnd);
};
