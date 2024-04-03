#include <iostream>
#include "Multiset.h"

void Multiset::copyFrom(const Multiset& other) {
	this->size = other.size;
	buckets = new uint8_t[size]{0};
	for (int i = 0;i < size;i++) {
		this->buckets[i] = other.buckets[i];
	}
	this->padding = other.padding;
	this->n = other.n;
}
void Multiset::free() {
	delete[] buckets;
}
int Multiset::getBoxIndex(uint32_t n) const{
	return n % (BUCKET_SIZE / 2);
}
int Multiset::getBucketIndex(uint32_t n) const{
	return n / (BUCKET_SIZE / 2);
}
Multiset::Multiset() {
	buckets = nullptr;
	size = 0;
	n = 0;
	padding = 2;
}
int Multiset::getNumber(int bucketIndex, int boxIndex) const {
	return bucketIndex * (BUCKET_SIZE / 2) + boxIndex;
}
void Multiset::printBox(int bucketIndex) const
{
	int end = BUCKET_SIZE / 2;
	for (int i = 0;i < end;i++) {
		printNumber(bucketIndex, i);
	}
}
void Multiset::printNumber(int bucketIndex, int boxIndex) const {
	int mask = 3;
	mask <<= padding * boxIndex;
	mask &= buckets[bucketIndex];
	mask >>= padding * boxIndex;
	int number = getNumber(bucketIndex, boxIndex);
	for (int i = 1;i <= mask;i++) {
		std::cout << number << ",";
	}
}
Multiset::Multiset(uint32_t n)
{
	this->n = n;
	padding = 2;
	size = (n / padding) + 1;
	buckets = new uint8_t[size]{0};
}
Multiset::Multiset(const Multiset& other) {
	copyFrom(other);
}

Multiset& Multiset::operator=(const Multiset& rhs)
{
	if (this != &rhs) {
		free();
		copyFrom(rhs);
	}
	return *this;
}

Multiset::~Multiset()
{
	free();
}

void Multiset::add(uint32_t n)
{
	if (this->n < n)return;
	int bucketIndex = getBucketIndex(n);
	int boxIndex = getBoxIndex(n);
	int mask = 3;
	mask <<= boxIndex * padding;
	mask &= buckets[bucketIndex];
	mask >>= boxIndex * padding;
	if (mask == 3)return;
	int bit = 1;
	bit <<= boxIndex * padding;
	buckets[bucketIndex] += bit;
}

void Multiset::print() const
{
	std::cout << "{";
	for (int i = 0;i < size;i++) {
		printBox(i);
	}
	std::cout << "}";
}

void Multiset::remove(uint32_t n)
{
	if (this->n < n)return;
	int bucketIndex = getBucketIndex(n);
	int boxIndex = getBoxIndex(n);
	int mask = 3;
	mask <<= boxIndex * padding;
	mask &= buckets[bucketIndex];
	mask >>= boxIndex * padding;
	if (mask > 0) {
		int bit = 1;
		bit <<= boxIndex * padding;
		buckets[bucketIndex] -= bit;
	}
}

int Multiset::countAppearances(uint32_t n) const
{
	if (this->n < n)return 0;
	int bucketIndex = getBucketIndex(n);
	int boxIndex = getBoxIndex(n);
	int mask = 3;
	mask <<= boxIndex * padding;
	mask &= buckets[bucketIndex];
	mask >>= boxIndex * padding;
	return mask;
}
//intersection
void Multiset::addMultipleNumbers(uint32_t number, size_t count) {
	for (int i = 1;i <= BUCKET_SIZE/2;i++) {
		remove(number);
	}
	for (int i = 1;i <= count;i++) {
		add(number);
	}
}
Multiset& Multiset::operator&=(const Multiset& rhs)
{
	if (this == (&rhs))return (*this);
	size_t minBuckets = size > rhs.size ? rhs.size : size;
	for (int i = 0;i < minBuckets;i++) {
		for (int j = 0;j < BUCKET_SIZE / 2;j++) {
			int number = getNumber(i, j);
			int set1Appear = this->countAppearances(number);
			int rhsAppear = rhs.countAppearances(number);
			int minAppearances = set1Appear < rhsAppear ? set1Appear : rhsAppear;
			addMultipleNumbers(number, minAppearances);
		}
	}
	return (*this);
}
//union


Multiset& Multiset::operator|=(const Multiset& rhs) {
	if (this == (&rhs))return (*this);
	size_t maxBuckets = size < rhs.size ? rhs.size : size;
	for (int i = 0;i < maxBuckets;i++) {
		for (int j = 0;j < BUCKET_SIZE / 2;j++) {
			int number = getNumber(i, j);
			int set1Appear = this->countAppearances(number);
			int rhsAppear = rhs.countAppearances(number);
			int maxAppearances = set1Appear > rhsAppear ? set1Appear : rhsAppear;
			addMultipleNumbers(number, maxAppearances);
		}
	}
	return (*this);
}