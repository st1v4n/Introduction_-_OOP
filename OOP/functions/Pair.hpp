#pragma once
#include <iostream>
#include <fstream>
namespace Symbols {
	const char FUNCTION_SYMBOL = 'f';
}
using namespace Symbols;
template <typename Left,typename Right>
class Pair {
public:
	Pair() {}
	Pair(const Left& newX, const Right& newY) : x(newX), y(newY) {}
	void setX(const Left& newX);
	void setY(const Right& newY);
	const Left& getX() const;
	const Right& getY() const;
	void printAsFunction() const;
	bool operator>(const Pair<Left, Right>& other);
private:
	Left x = 0;
	Right y = 0;
};

template<typename Left, typename Right>
inline void Pair<Left, Right>::setX(const Left& newX)
{
	this->x = newX;
}

template<typename Left, typename Right>
inline void Pair<Left, Right>::setY(const Right& newY)
{
	this->y = newY;
}

template<typename Left, typename Right>
inline const Left& Pair<Left, Right>::getX() const
{
	return x;
}

template<typename Left, typename Right>
inline const Right& Pair<Left, Right>::getY() const
{
	return y;
}

template<typename Left, typename Right>
inline void Pair<Left, Right>::printAsFunction() const
{
	std::cout << FUNCTION_SYMBOL << '(' << x << ')' << " = " << y << '\n';
}

template<typename Left, typename Right>
inline bool Pair<Left, Right>::operator>(const Pair<Left, Right>& other)
{
	if (this->x == other.x) {
		return this->y > other.y;
	}
	return false;
}
