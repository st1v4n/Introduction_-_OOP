#include "Multiset.h"

unsigned getLower(unsigned number, unsigned number2)
{
	return (number < number2 ? number : number2);
}

void swapNumbers(unsigned& number, unsigned& number2)
{
	unsigned temp = number;
	number = number2;
	number2 = temp;
}

unsigned getAbsDifference(unsigned number, unsigned number2)
{
	//because they are unsigned numbers
	if (number < number2)swapNumbers(number, number2);
	return number - number2;
}

unsigned getBigger(unsigned number, unsigned number2)
{
	return (number > number2 ? number : number2);
}

int Multiset::getRightAddress(int number) const
{
		return (number * k);
}

int Multiset::getLeftAddress(int number) const
{
	return getRightAddress(number) + k - 1;
}

int Multiset::getBucketsCount() const
{
	int leftAddress = getLeftAddress(n);
	return leftAddress / MAX_BITS + 1;
}


int Multiset::getBucketIndex(int address) const
{
	return address / MAX_BITS;
}

unsigned Multiset::getMaxOccurences() const
{
	unsigned powerOfTwo = (1 << k);
	return powerOfTwo - 1;
}

int Multiset::getBitIndex(int address) const
{
	return  address % MAX_BITS;
}

uint8_t Multiset::getBit(int bucketIndex, int bitIndex) const
{
	//we get what the bit is on that specific position in the bucket
	uint8_t bit = 1;
	bit <<= bitIndex;
	bit &= buckets[bucketIndex];
	bit >>= bitIndex;
	return bit;
}

unsigned Multiset::countNumberAppearances(int number) const
{
	    //this is the private function, the function mention in the task is later
		//in this variable we will store the count of all the appearances of the number in the multiset
	    if (number > n || number < 0)return 0;
		unsigned countAppearances = 0;
		int rightAddress = getRightAddress(number);
		int leftAddress = getLeftAddress(number);
		for (int i = rightAddress, multiplier = 1;i <= leftAddress;i++, multiplier *= 2) {
			//because they could be in different buckets
			int bucketIndex = getBucketIndex(i);
			int bitIndex = getBitIndex(i);
			//now we know the bucket and the index of each address, so it is time to get each bit and create a new number by converting from binary to decimal
			countAppearances += getBit(bucketIndex, bitIndex) * multiplier;
		}
		return countAppearances;
}

void Multiset::setBit(int bucketIndex, int bitIndex, uint8_t bit)
{
	//Introduction to programming course type of exercise :)
	if (bit == 0) {
		bit = 1;
		bit <<= bitIndex;
		bit= ~bit;
		buckets[bucketIndex] &= bit;
	}
	else {
		bit <<= bitIndex;
		buckets[bucketIndex] |= bit;
	}
}

void Multiset::setCount(int number, unsigned countAppearances)
{
	int leftAddress = getLeftAddress(number);
	int rightAddress = getRightAddress(number);
	for (int i = rightAddress;i <= leftAddress;i++) {
		//because they could be in different buckets
		int bucketIndex = getBucketIndex(i);
		int bitIndex = getBitIndex(i);
		//we get the last bit from the countAppearances variable
		// after that we set that bit into the bucket on the correct index
		// and we shift countAppearances to the right by 1 to remove the bit we already got
		uint8_t bit = (countAppearances % 2 == 0) ? 0 : 1;
		setBit(bucketIndex, bitIndex, bit);
		countAppearances >>= 1;
	}
}

void Multiset::free()
{
	delete[] buckets;	
	n = 0;
	k = 1;
}

void Multiset::copyFrom(const Multiset& other)
{
	try {
		this->n = other.n;
		this->k = other.k;
		int bucketsCount = getBucketsCount();
		buckets = new uint8_t[bucketsCount];
		for (int i = 0;i < bucketsCount;i++) {
			buckets[i] = other.buckets[i];
		}
	}
	catch (const std::exception& ex) {
		std::cout << "Error occured while copying!";
		throw;
	}
	catch (...) {
		std::cout << "Unexpected error!";
		free();
		throw;
	}
}

void Multiset::printNumber(std::ostream& os, int number, int countAppearances) const
{
	for (int i = 1;i <= countAppearances;i++) {
		os << number << ", ";
	}
}

void Multiset::fromDecimalToBinary(uint8_t number, char* buffer) const
{
	for (int i = MAX_BUFFER_SIZE-2;i >= 0;i--) {
		char bit = (number % 2 == 0) ? '0' : '1';
		buffer[i] = bit;
		number >>= 1;
	}
}

void Multiset::moveFrom(Multiset&& other)
{
	buckets = other.buckets;
	other.buckets = nullptr;
	n = other.n;
	k = other.k;
}

Multiset::Multiset(int n, int k)
{
	try {
		if (n < 0 || (k<MIN_BITS || k>MAX_BITS)) {
			throw ERROR_EXCEPTION;
		}
		else {
			this->n = n;
			this->k = k;
			int bucketsCount = getBucketsCount();
			buckets = new uint8_t[bucketsCount]{ 0 };
		}
	}
	catch (const std::exception& ex) {
		std::cout << "Exception occured while trying to create the object!";
		throw;
	}
	catch (const char* str) {
		std::cout << "Invalid values for n or k!";
		throw;
	}
	catch (...) {
		std::cout << "Unexpected error!";
		throw;
	}
}

Multiset::Multiset(const Multiset& other)
{
	copyFrom(other);
}

Multiset& Multiset::operator=(const Multiset& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return (*this);
}

Multiset::Multiset(Multiset&& other) noexcept
{
	moveFrom(std::move(other));
}

Multiset& Multiset::operator=(Multiset&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Multiset::~Multiset()
{
	free();
}


int Multiset::getN() const
{
	return n;
}

int Multiset::getK() const
{
	return k;
}

void Multiset::add(int number)
{
	try {
		if (number > n || number < 0 || buckets == nullptr) {
			throw ERROR_EXCEPTION;
		}
		else {
			unsigned countAppearances = countNumberAppearances(number);
			if (countAppearances >= getMaxOccurences()) {
				return;
			}
			else {
				countAppearances++;
				setCount(number, countAppearances);
			}
		}
	}
	catch (...) {
		free();
		throw;
	}
}

unsigned Multiset::getNumberAppearances(int number) const
{
		return countNumberAppearances(number);
}

void Multiset::print() const
{
	if (buckets == nullptr) {
		std::cout << "{}";
		return;
	}
	std::cout << "{ ";
	for (int i = 0;i <= n;i++) {
		int countAppearances = countNumberAppearances(i);
		printNumber(std::cout, i, countAppearances);
	}
	std::cout << " }";
}

std::ostream& operator<<(std::ostream& os, const Multiset& set)
{
	if (set.buckets == nullptr) {
		os << "{}";
		return os;
	}
	os << "{ ";
	for (int i = 0;i <= set.n;i++) {
		int countAppearances = set.countNumberAppearances(i);
		set.printNumber(os, i, countAppearances);
	}
	os << " }";
	return os;
}

void Multiset::printByMemory() const
{
	//we imagine the buckets starting from right to left, but in the memory they start from left to right
	// the far left bucket is buckets[0]
	if (buckets == nullptr)return;
	int countBuckets = getBucketsCount();
	for (int i = 0;i < countBuckets;i++) {
		char buffer[MAX_BUFFER_SIZE];
		buffer[MAX_BUFFER_SIZE - 1] = '\0';
		fromDecimalToBinary(buckets[i], buffer);
		std::cout << buffer << ' ';
	}
}

void Multiset::saveToBinaryFile(std::ofstream& ofs) const
{
	if (!ofs.is_open()) {
		std::cout << "File is not open!"<<std::endl;
		return;
	}
	ofs.write((const char*)&n, sizeof(unsigned));
	ofs.write((const char*)&k, sizeof(unsigned));
	if (buckets != nullptr) {
		unsigned bucketCount = getBucketsCount();
		ofs.write((const char*)buckets, bucketCount * sizeof(uint8_t));
	}
	ofs.clear();
	ofs.seekp(std::ios::beg, 0);
}

void Multiset::readFromBinaryFile(std::ifstream& ifs)
{
	try {
		if (!ifs.is_open()) {
			std::cout << "File is not open!" << std::endl;
			return;
		}
		ifs.read((char*)&n, sizeof(unsigned));
		ifs.read((char*)&k, sizeof(unsigned));
		if (k<MIN_BITS || k>MAX_BITS || n < 0) {
			free();
			throw ERROR_EXCEPTION;
		}
		unsigned bucketCount = getBucketsCount();
		delete[] buckets;
		buckets = new uint8_t[bucketCount]{ 0 };
		ifs.read((char*)buckets, bucketCount * sizeof(uint8_t));
		ifs.clear();
		ifs.seekg(std::ios::beg, 0);
	}
	catch (const std::exception& ex) {
		std::cout << "Exception occured while trying to read from file!";
		free();
		throw;
	}
	catch (const char* str) {
		std::cout << "Invalid values for n or k!";
		free();
		throw;
	}
	catch (...) {
		std::cout << "Unexpected error!";
		free();
		throw;
	}
}
Multiset intersection(const Multiset& set1, const Multiset& set2)
{
	if (set1.buckets == nullptr || set2.buckets == nullptr) {
		//the empty set
		return Multiset();
	}
	unsigned intersectionN = getLower(set1.n, set2.n);
	unsigned intersectionK = getLower(set1.k, set2.k);
	Multiset intersectionSet(intersectionN, intersectionK);
	for (int i = 0;i <= intersectionN;i++) {
		unsigned countInSet1 = set1.countNumberAppearances(i);
		unsigned countInSet2 = set2.countNumberAppearances(i);
		unsigned countInIntersection = getLower(countInSet1, countInSet2);
		if (countInIntersection != 0) {
			intersectionSet.setCount(i, countInIntersection);
		}
	}
	return intersectionSet;
}

Multiset& Multiset::operator/=(const Multiset& other)
{
	//if we have the empty set
	if (buckets == nullptr || other.buckets == nullptr) {
		return *this;
	}
	for (int i = 0;i <= n;i++) {
		unsigned countInSet1 = countNumberAppearances(i);
		unsigned countInOther = other.countNumberAppearances(i);
		unsigned countInResult = 0;
		if (countInSet1 > countInOther)countInResult = countInSet1 - countInOther;
		if (countInResult != 0) {
			setCount(i, countInResult);
		}
	}
	return *this;
}

Multiset operator/(const Multiset& set1, const Multiset& set2)
{
	//if we have the empty set
	if (set1.buckets == nullptr || set2.buckets==nullptr) {
		return set1;
	}
	Multiset result(set1);
	result /= set2;
	return result;
}

Multiset difference(const Multiset& set1, const Multiset& set2)
{
	//if set1 is the empty set
	if (set1.buckets == nullptr) {
		return set2;
	}
	//if set2 is the empty set
	if (set2.buckets == nullptr) {
		return set1;
	}
	unsigned resultN = getBigger(set1.n, set2.n);
	unsigned resultK = getBigger(set1.k, set2.k);
	Multiset result(resultN, resultK);
	for (int i = 0;i <= resultN;i++) {
		unsigned countInSet1 = set1.countNumberAppearances(i);
		unsigned countInSet2 = set2.countNumberAppearances(i);
		unsigned countInResult = getAbsDifference(countInSet1,countInSet2);
		if (countInResult != 0) {
			result.setCount(i, countInResult);
		}
	}
	return result;
}

Multiset getSetAddition(const Multiset& set)
{
	//if its the empty set, the addition is infinite + we dont know info about n and k
	if (set.buckets == nullptr) {
		std::cout << "Infinite Set!";
		return Multiset();
	}
	Multiset addition(set.n, set.k);
	unsigned bucketsCount = set.getBucketsCount();
	for (int i = 0;i < bucketsCount;i++) {
		addition.buckets[i] = ~set.buckets[i];
	}
	return addition;
}

