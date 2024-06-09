#pragma once
#include <iostream>
#include <fstream>
//all comments are about the thing BELOW them
//all comments are in english, because c++ does not support BG alphabet
namespace MULTISET_CONSTANTS {
	const char ERROR_EXCEPTION[6] = "ERROR";
	const size_t MIN_BITS = 1;
	const size_t MAX_BITS = 8;
	constexpr size_t MAX_BUFFER_SIZE = MAX_BITS + 1;//for the '\0' at the end
}
using namespace MULTISET_CONSTANTS;
static unsigned getLower(unsigned number, unsigned number2);
static void swapNumbers(unsigned& number, unsigned& number2);
static unsigned getAbsDifference(unsigned number, unsigned number2);
static unsigned getBigger(unsigned number, unsigned number2);
class Multiset {
private:
	int n = 0;
	int k = 1;
	// we have buckets, similar to the exercise we did at the Practicum course
	uint8_t* buckets = nullptr;
	// we have buckets, each of them having 8 addresses (they are 8 bits). We will create a function to see which address does a specific number belong to
    // we will only find the right address, the left is easy calculated with the formula (right + k - 1);
	//for example:
	// buckets[0] has addresses from 0 (right) to 7 (left)
	// buckets[1] has addresses from 8(left) to 15(right)
	// so our goal is to find which at which interval of addresses is our number stored
	int getRightAddress(int number) const;
	int getLeftAddress(int number) const;
	//classic Introduction to programming type of functions, in the private part because they are not supposed to be seen by the customer
	int getBucketsCount() const;
	int getBucketIndex(int address) const;
	unsigned getMaxOccurences() const;
	//that is the function which finds the address (from 0 to 7) in the current bucket
	int getBitIndex(int address) const;
	uint8_t getBit(int bucketIndex, int bitIndex) const;
	// this is the private count Number Appearances function (used for other functions), the function mentioned in the task is defined later
	unsigned countNumberAppearances(int number) const;
	void setBit(int bucketIndex, int bitIndex, uint8_t bit);
	void setCount(int number, unsigned countAppearances);
	void free();
	void copyFrom(const Multiset& other);
	void printNumber(std::ostream& os, int number, int countAppearances) const;
	void fromDecimalToBinary(uint8_t number, char* buffer) const;
	void moveFrom(Multiset&& other);
public:
	Multiset() = default;
	Multiset(int n, int k);
	Multiset(const Multiset& other);
	Multiset& operator=(const Multiset& other);
	Multiset(Multiset&& other) noexcept;
	Multiset& operator=(Multiset&& other) noexcept;
	~Multiset();
	int getN() const;
	int getK() const;
	void add(int number);
	unsigned getNumberAppearances(int number) const;
	//we will have two ways of printing - 1) print function and 2) operator<< redefinition
	//print works only for printing on the console, while operator<< is more abstract
	void print() const;
	friend std::ostream& operator<<(std::ostream& os, const Multiset& set);
	//the way the multiset is presented in the memory (in binary)
	//we imagine the buckets starting from right to left, but in the memory they start from left to right
	// the far left bucket is buckets[0]
	void printByMemory() const;
	void saveToBinaryFile(std::ofstream& ofs) const;
	void readFromBinaryFile(std::ifstream& ifs);
	friend Multiset intersection(const Multiset& set1, const Multiset& set2);
	//we will have two different implementations of the difference between two multisets
	//the first one will the the operator / , which will give all the elements that are contained in the first Multiset, but not in the second
	//the second one will be called "difference" and will return a Multiset, which contains all elements that differ the two sets
	// Example for the operator / :       set1: {3,3,3,3,4};
	//                                    set2: {3,3,5};
	//                                    Result: {3,3,4}; 
	//Example for the function difference: set1: {3,3,3,3,4};
	//                                     set2: {3,3,5};
	//                                     Result: {3,3,4,5};
	Multiset& operator/=(const Multiset& other);
	friend Multiset operator/(const Multiset& set1, const Multiset& set2);
	friend Multiset difference(const Multiset& set1, const Multiset& set2);
	//the addition of the set is a new set
	friend Multiset getSetAddition(const Multiset& set);
};
