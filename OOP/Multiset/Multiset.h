#pragma once
const int BUCKET_SIZE = 8;
class Multiset {
private:
	uint8_t* buckets;
	size_t size;
	uint32_t n;
	uint8_t padding;
	void copyFrom(const Multiset& other);
	void free();
	int getBucketIndex(uint32_t n) const;
	int getBoxIndex(uint32_t n) const;
	int getNumber(int bucketIndex, int boxIndex) const;
	void printBox(int bucketIndex) const;
	void printNumber(int bucketIndex, int boxIndex) const;
	void addMultipleNumbers(uint32_t number, size_t count);
public:
	Multiset();
	explicit Multiset(uint32_t n);
	Multiset(const Multiset& other);
	Multiset& operator=(const Multiset& rhs);
	~Multiset();
	void add(uint32_t n);
	void remove(uint32_t n);
	int countAppearances(uint32_t n) const;
	void print() const;
	// intersection will not be a separate function, it will be defined as the operator &=
	Multiset& operator&=(const Multiset& rhs);
	//union will be the operator |=
	Multiset& operator|=(const Multiset& rhs);
};
