#pragma once
#include "PartialFunction.h"
#include "Container.hpp"
class MaximumFunction : public PartialFunction {
private:
	Container functions;
public:
	MaximumFunction(const Container& container);
	Pair<int32_t, int32_t> operator()(int32_t x) const override;
	bool isDefined(int32_t x) const override;
	PartialFunction* clone() const override;
};

inline MaximumFunction::MaximumFunction(const Container& container)
{
	functions = container;
}
Pair<int32_t, int32_t> MaximumFunction::operator()(int32_t x) const {
	if (isDefined(x)) {
	int32_t maxY = (*functions.getFunction(0))(x).getY();
	size_t containerSize = functions.getSize();
	for (size_t i = 1;i < containerSize; i++) {
		int32_t value = (*functions.getFunction(i))(x).getY();
		if (value > maxY)maxY = value;
	}
	Pair<int32_t, int32_t> result(x, maxY);
	return result;
	}
	throw std::logic_error("Point is undefined!");
}
bool MaximumFunction::isDefined(int32_t x) const {
	size_t containerSize = functions.getSize();
	for (size_t i = 0; i < containerSize; i++) {
		if (!functions.getFunction(i)->isDefined(x))return false;
	}
	return true;
}
PartialFunction* MaximumFunction::clone() const {
	return new MaximumFunction(*this);
}
