#include "ModifiableIntegersFunction.h"

void EXCEPTION_HANDLE(int exceptionCode)
{
	switch (exceptionCode) {
	case (int)FUNCTION_EXEPTIONS::NULLPTR_EXCEPTION: std::cout << "Nullptr detected! Invalid Input!";break;
	case (int)FUNCTION_EXEPTIONS::INVALID_VALUE: std::cout << "Value out of allowed range!";break;
	case (int)FUNCTION_EXEPTIONS::UNDEFINED_EXCEPTION: std::cout << "Function is not defined in this point!";break;
	default: std::cout << "Unexpected error!" << std::endl;break;
	}
}

ModifiableIntegersFunction::ModifiableIntegersFunction(int16_t(*func)(int16_t))
{
	try {
		setFunction(func);
		modified_points = new ModifiedPoints[capacity];
	}
	catch (int exceptionCode) {
		EXCEPTION_HANDLE(exceptionCode);
		throw;
	}
	catch (...) {
		std::cout << "Unknown error!";
		throw;
	}
}

ModifiableIntegersFunction::ModifiableIntegersFunction(const ModifiableIntegersFunction& other)
{
	copyFrom(other);
}

ModifiableIntegersFunction::ModifiableIntegersFunction(ModifiableIntegersFunction&& other) noexcept
{
	moveFrom(std::move(other));
}

ModifiableIntegersFunction& ModifiableIntegersFunction::operator=(const ModifiableIntegersFunction& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

ModifiableIntegersFunction& ModifiableIntegersFunction::operator=(ModifiableIntegersFunction&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

ModifiableIntegersFunction::~ModifiableIntegersFunction()
{
	free();
}

void ModifiableIntegersFunction::setFunction(int16_t(*func)(int16_t))
{
	if (func == nullptr)throw (int)FUNCTION_EXEPTIONS::NULLPTR_EXCEPTION;
	this->function = func;
}

int ModifiableIntegersFunction::getBucketIndex(uint16_t x) const
{
	return x / MAX_BITS;
}

int ModifiableIntegersFunction::getBitIndex(uint16_t x) const
{
	return x % MAX_BITS;
}

void ModifiableIntegersFunction::setBit(uint8_t& bucket, int bitIndex, uint8_t bit)
{
	if (bit == 0) {
		bit = 1;
		bit <<= bitIndex;
		bit = ~bit;
		bucket &= bit;
	}
	else {
		bit <<= bitIndex;
		bucket |= bit;
	}
}

bool ModifiableIntegersFunction::getBit(uint8_t bucket, int bitIndex) const
{
	int bit = 1;
	bit <<= bitIndex;
	bit &= bucket;
	return bit;
}

bool ModifiableIntegersFunction::isModified(uint16_t x) const
{
	uint16_t bucketIndex = getBucketIndex(x);
	uint8_t bitIndex = getBitIndex(x);
	return getBit(is_modified_buckets[bucketIndex], bitIndex);
}

bool ModifiableIntegersFunction::isDefined(uint16_t x) const
{
	int bucketIndex = getBucketIndex(x);
	int bitIndex = getBitIndex(x);
	//because if the bit is 1, its not defined. If the bit is 0,its defined
	return !getBit(undefined_buckets[bucketIndex], bitIndex);
}

void ModifiableIntegersFunction::free()
{
	function = default_function;
	delete[] modified_points;
	size = 0;
	capacity = 4;
	for (int i = 0;i < MAX_BUCKET_SIZE;i++) {
		undefined_buckets[i] = 0;
		is_modified_buckets[i] = 0;
	}
}

void ModifiableIntegersFunction::copyFrom(const ModifiableIntegersFunction& other)
{
	try {
		this->function = other.function;
		this->size = other.size;
		this->capacity = other.capacity;
		for (int i = 0;i < MAX_BUCKET_SIZE;i++) {
			undefined_buckets[i] = other.undefined_buckets[i];
			is_modified_buckets[i] = other.is_modified_buckets[i];
		}
		modified_points = new ModifiedPoints[capacity];
		for (int i = 0;i < capacity;i++) {
			modified_points[i] = other.modified_points[i];
		}
	}
	catch (...) {
		std::cout << "Failed while trying to copy from Other!";
		delete[] other.modified_points;
		throw;
	}
}

void ModifiableIntegersFunction::moveFrom(ModifiableIntegersFunction&& other)
{
	this->function = other.function;
	other.function = default_function;
	this->modified_points = other.modified_points;
	other.modified_points = nullptr;
	this->size = other.size;
	other.size = 0;
	this->capacity = other.capacity;
	other.capacity = 4;
	for (int i = 0;i < MAX_BUCKET_SIZE;i++) {
		undefined_buckets[i] = other.undefined_buckets[i];
		is_modified_buckets[i] = other.is_modified_buckets[i];
		other.undefined_buckets[i] = 0;
		other.is_modified_buckets[i] = 0;
	}
}

void ModifiableIntegersFunction::resize()
{
	try {
		ModifiableIntegersFunction copy(*this);
		delete[] this->modified_points;
		this->capacity *= CAPACITY_TO_SIZE;
		modified_points = new ModifiedPoints[capacity];
		for (int i = 0;i < copy.size;i++) {
			modified_points[i] = copy.modified_points[i];
		}
	}
	catch (...) {
		std::cout << "Failed while trying to allocate data!";
		throw;
	}
}

void ModifiableIntegersFunction::setModified(uint16_t x)
{
	unsigned bucketIndex = getBucketIndex(x);
	unsigned bitIndex = getBitIndex(x);
	setBit(is_modified_buckets[bucketIndex], bitIndex, 1);
}

int16_t ModifiableIntegersFunction::findValue(int16_t x) const
{
	for (int i = 0;i < size;i++) {
		if (modified_points[i].x == x)return modified_points[i].modifiedY;
	}
}

void ModifiableIntegersFunction::setFunctionalValue(int16_t x, int16_t& y) const
{
	if (!isDefined(x)) {
		y = MIN_NUMBER;
		return;
	}
	if (isModified(x)) y = findValue(x);
	else {
		y = function(x);
	}
}

void ModifiableIntegersFunction::setSpecificValue(int16_t x, int16_t y)
{
	try {
		if (!isDefined(x))throw (int)FUNCTION_EXEPTIONS::UNDEFINED_EXCEPTION;
		if (isModified(x)) {
			//if this x was already modified, we want to set him a new modifiedY, instead of creating a new point
			for (int i = 0;i < size;i++) {
				if (modified_points[i].x == x) {
					modified_points[i].modifiedY = y;
					break;
				}
			}
		}
		else {
			if (size >= capacity)resize();
			modified_points[size].x = x;
			modified_points[size].modifiedY = y;
			setModified(x);
			++size;
		}
	}
	catch (int exceptionCode) {
		EXCEPTION_HANDLE(exceptionCode);
		return;
	}
	catch (...) {
		std::cout << "Unknown error!";
		throw;
	}
}

void ModifiableIntegersFunction::setUndefined(int16_t x)
{
	int bucketIndex = getBucketIndex((uint16_t)x);
	int bitIndex = getBitIndex((uint16_t)x);
	uint8_t bit = 1;
	setBit(undefined_buckets[bucketIndex], bitIndex, bit);
}

int16_t ModifiableIntegersFunction::getValue(int16_t x) const
{
	try{
		if (!isDefined(x))throw (int)FUNCTION_EXEPTIONS::UNDEFINED_EXCEPTION;
		if (isModified(x)) {
			for (int i = 0;i < size;i++) {
				if (modified_points[i].x == x) {
					return modified_points[i].modifiedY;
				}
			}
		}
		else {
			return function(x);
		}
	}
	catch (int exceptionCode) {
		EXCEPTION_HANDLE(exceptionCode);
		return 0;
	}
	catch (...) {
		std::cout << "Unexpected error!";
		return 0;
	}
}

int16_t ModifiableIntegersFunction::operator()(int16_t x) const
{
	return getValue(x);
}

ModifiableIntegersFunction operator+(const ModifiableIntegersFunction& f, const ModifiableIntegersFunction& g)
{
	ModifiableIntegersFunction result;
	try {
		//in the result function all values will be modifiend - they will be a sum of the values from f(x) and g(x) result(x) = f(x)+g(x);
		result.size = result.capacity = MAX_SIZE;
		result.modified_points = new ModifiedPoints[result.capacity];
		for (int i = 0;i < MAX_BUCKET_SIZE;i++) {
			//we do that because we want to set all points as modified, and after than we set their values (changing the function pointer is impossible)
			result.is_modified_buckets[i] = UINT8_MAX;
		}
		for (int i = MIN_NUMBER; i <= MAX_NUMBER;i++) {
			if (!f.isDefined(i) || !g.isDefined(i)) {
				result.setUndefined(i);
			}
			else {
				result.modified_points[(uint16_t)i].x = i;
				result.modified_points[(uint16_t)i].modifiedY = f(i) + g(i);
			}
		}
		return result;
	}
	catch (...) {
		std::cout << "Error occured while summing!";
		result.free();
		throw;
	}
}

ModifiableIntegersFunction operator-(const ModifiableIntegersFunction& f, const ModifiableIntegersFunction& g)
{
	ModifiableIntegersFunction result;
	try {
		//in the result function all values will be modifiend - they will be a sum of the values from f(x) and g(x) result(x) = f(x)-g(x); for every x
		result.size = result.capacity = MAX_SIZE;
		result.modified_points = new ModifiedPoints[result.capacity];
		for (int i = 0;i < MAX_BUCKET_SIZE;i++) {
			result.is_modified_buckets[i] = UINT8_MAX;
		}
		for (int i = MIN_NUMBER; i <= MAX_NUMBER;i++) {
			if (!f.isDefined(i) || !g.isDefined(i)) {
				result.setUndefined(i);
			}
			else {
				result.modified_points[(uint16_t)i].x = i;
				result.modified_points[(uint16_t)i].modifiedY = f(i) - g(i);
			}
		}
		return result;
	}
	catch (...) {
		std::cout << "Error occured while summing!";
		result.free();
		throw;
	}
}


int16_t ModifiableIntegersFunction::operator[](int16_t x) const
{
	try {
		if (!isDefined(x))throw (int)FUNCTION_EXEPTIONS::UNDEFINED_EXCEPTION;
		if (isModified(x)) {
			for (int i = 0;i < size;i++) {
				if (modified_points[i].x == x) {
					return modified_points[i].modifiedY;
				}
			}
		}
		else {
			return function(x);
		}
	}
	catch (int exceptionCode) {
		EXCEPTION_HANDLE(exceptionCode);
		return 0;
	}
	catch (...) {
		std::cout << "Unknown error!";
		throw;
	}
}

ModifiableIntegersFunction& ModifiableIntegersFunction::operator[](const ModifiableIntegersFunction& other)
{
	try {
		//in the result function all values will be modifiend - they will be a sum of the values from f(x) and g(x) result(x) = f(x)+g(x);
		size = capacity = MAX_SIZE;
		for (int i = 0;i < MAX_BUCKET_SIZE;i++) {
			is_modified_buckets[i] = UINT8_MAX;
		}
		for (int i = MIN_NUMBER; i <= MAX_NUMBER;i++) {
			if (!other.isDefined(i)) {
				setUndefined(i);
			}
		}
		modified_points = new ModifiedPoints[capacity];
		for (int i = MIN_NUMBER;i <= MAX_NUMBER;i++) {
			if (!isDefined(i))continue;
			int x = other.getValue(i);
			modified_points[(uint16_t)i].x = x;
			modified_points[(uint16_t)i].modifiedY = function(x);
		}
		return *this;
	}
	catch (...) {
		std::cout << "Error occured while operating!";
		free();
		throw;
	}
}

bool ModifiableIntegersFunction::operator>(const ModifiableIntegersFunction& other) const
{
	for (int i = MIN_NUMBER;i <= MAX_NUMBER;i++) {
		int16_t thisY;
		int16_t otherY;
		setFunctionalValue(i, thisY);
		other.setFunctionalValue(i, otherY);
		if (thisY <= otherY)return false;
	}
	return true;
}

bool ModifiableIntegersFunction::operator<(const ModifiableIntegersFunction& other) const
{
	for (int i = MIN_NUMBER;i <= MAX_NUMBER;i++) {
		int16_t thisY;
		int16_t otherY;
		setFunctionalValue(i, thisY);
		other.setFunctionalValue(i, otherY);
		if (thisY >= otherY)return false;
	}
	return true;
}

bool ModifiableIntegersFunction::operator==(const ModifiableIntegersFunction& other) const
{
	for (int i = MIN_NUMBER;i <= MAX_NUMBER;i++) {
		int16_t thisY;
		int16_t otherY;
		setFunctionalValue(i, thisY);
		other.setFunctionalValue(i, otherY);
		if (thisY != otherY)return false;
	}
	return true;
}

bool ModifiableIntegersFunction::operator!=(const ModifiableIntegersFunction& other) const
{
	return !((*this) == other);
}

bool operator||(const ModifiableIntegersFunction& f, const ModifiableIntegersFunction& g)
{
	// if two functions are paralle, their values will be separated by a constant and they wont have a gathering point
	int16_t constant = f.getValue(MIN_NUMBER) - g.getValue(MIN_NUMBER);
	for (int i = MIN_NUMBER + 1;i <= MAX_NUMBER;i++) {
		if (f.getValue(i) - g.getValue(i) != constant)return false;
	}
	return true;
}

ModifiableIntegersFunction operator~(const ModifiableIntegersFunction& f)
{
	ModifiableIntegersFunction result;
	try {	
		result.size = result.capacity = MAX_SIZE;
		result.modified_points = new ModifiedPoints[result.capacity];
		for (int i = 0;i < MAX_BUCKET_SIZE;i++) {
			result.is_modified_buckets[i] = UINT8_MAX;
		}
		for (int i = MIN_NUMBER;i <= MAX_NUMBER;i++) {
			if (!f.isDefined(i)) {
				result.setUndefined(i);
			}
			else {
				result.modified_points[(uint16_t)i].x = f(i);
				result.modified_points[(uint16_t)i].modifiedY = i;
			}
		}
		return result;
	}
	catch (int exceptionCode) {
		EXCEPTION_HANDLE(exceptionCode);
		result.free();
		return {};
	}
	catch (...) {
		std::cout << "Unknown error!";
		result.free();
		throw;
	}
}

bool ModifiableIntegersFunction::isInjective() const
{
	//we will do a bit set bucket, where we will store which Y values we passed already. If a specific Y value is passed to times, we return false
	uint8_t injectionBuckets[MAX_BUCKET_SIZE] = { 0 };
	for (int i = MIN_NUMBER;i <= MAX_NUMBER;i++) {
		int16_t value = getValue(i);
		int bucketIndex = getBucketIndex(value);
		int bitIndex = getBitIndex(value);
		if (getBit(injectionBuckets[bucketIndex], bitIndex)) {
			return false;
		}
		else {
			//if the bit was 0 (we didnt encounter this y before), we set it to 1
			uint8_t bit = 1;
			bit <<= bitIndex;
			injectionBuckets[bucketIndex] |= bit;
		}
	}
	return true;
}

bool ModifiableIntegersFunction::isSurection() const
{
	//we will create surectiveBuckets where we will store every Y value we passed. If at the end every bucket has the bits 11111111, it means that its surective. If at least one bit is 0, its not
	uint8_t surectiveBuckets[MAX_BUCKET_SIZE] = { 0 };
	for (int i = MIN_NUMBER;i <= MAX_NUMBER;i++) {
		int16_t value = getValue(i);
		int bucketIndex = getBucketIndex(value);
		int bitIndex = getBitIndex(value);
		uint8_t bit = 1;
		bit <<= bitIndex;
		surectiveBuckets[bucketIndex] |= bit;
	}
	for (int i = 0;i < MAX_BUCKET_SIZE;i++) {
		//checking if the bits are 11111111
		if (surectiveBuckets[i] != UINT8_MAX)return false;
	}
	return true;
}

bool ModifiableIntegersFunction::isBijection() const
{
	return isInjective() && isSurection();
}

void ModifiableIntegersFunction::saveToBinary(std::ofstream& ofs) const
{
	try {
		if (!ofs.is_open())throw "File not open!";
		for (int i = MIN_NUMBER; i <= MAX_NUMBER;i++) {
			if (isDefined(i)) {
				int16_t value = getValue(i);
				ofs.write((const char*)&i, sizeof(int16_t));
				ofs.write((const char*)&value, sizeof(int16_t));
			}
		}
		ofs.clear();
		ofs.seekp(0, std::ios::beg);
	}
	catch (...) {
		ofs.clear();
		ofs.seekp(0, std::ios::beg);
		throw;
	}
}

void ModifiableIntegersFunction::readFromBinary(std::ifstream& ifs)
{
	try{
		if (!ifs.is_open())throw "File not open!";
		free();
		modified_points = new ModifiedPoints[capacity];
		while (!ifs.eof()) {
			int16_t x;
			int16_t y;
			ifs.read((char*)&x, sizeof(int16_t));
			if (ifs.eof())return;
			ifs.read((char*)&y, sizeof(int16_t));
			setSpecificValue(x, y);
		}
	}
	catch (...) {
		free();
		ifs.clear();
		ifs.seekg(0, std::ios::beg);
		throw;
	}
}

void ModifiableIntegersFunction::drawFunctionInInterval(std::ostream& os, int16_t xStart, int16_t xEnd, int16_t yStart, int16_t yEnd)
{
	if (xEnd - xStart != INTERVAL_LENGTH || yEnd-yStart!=INTERVAL_LENGTH) {
		std::cout << "Invalid intervals!";
		return;
	}
	constexpr size_t INTERVAL_SIZE = INTERVAL_LENGTH + 1;
	//we will create matrix that will be empty at first and later we will add points to it
	char field[INTERVAL_SIZE][INTERVAL_SIZE];
	for (int i = 0;i < INTERVAL_SIZE;i++) {
		for (int j = 0;j < INTERVAL_SIZE;j++) {
			field[i][j] = ' ';
		}
	}
	for (int i = xStart;i <= xEnd;i++) {
		int16_t y = getValue(i);
		if (y > yEnd || y < yStart)continue;
		field[yEnd-y][i-xStart] = '*';
	}
	for (int i = 0;i < INTERVAL_SIZE;i++) {
		for (int j = 0;j < INTERVAL_SIZE;j++) {
			os << field[i][j];
		}
		os << '\n';
	}
}






