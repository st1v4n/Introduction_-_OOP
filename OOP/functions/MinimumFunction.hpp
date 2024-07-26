#pragma once
#include "PartialFunction.h"
#include "Container.hpp"
class MinimumFunction : public PartialFunction {
private:
	Container functions;
public:
	MinimumFunction(const Container& container);
	Pair<int32_t, int32_t> operator()(int32_t x) const override;
	bool isDefined(int32_t x) const override;
	PartialFunction* clone() const override;
};

inline MinimumFunction::MinimumFunction(const Container& container)
{
	functions = container;
}
Pair<int32_t, int32_t> MinimumFunction::operator()(int32_t x) const {
	if (isDefined(x)) {
		int32_t minY = (*functions.getFunction(0))(x).getY();
		size_t containerSize = functions.getSize();
		for (size_t i = 1;i < containerSize; i++) {
			int32_t value = (*functions.getFunction(i))(x).getY();
			if (value < minY)minY = value;
		}
		Pair<int32_t, int32_t> result(x, minY);
		return result;
	}
	throw std::logic_error("Point is undefined!");
}
bool MinimumFunction::isDefined(int32_t x) const {
	size_t containerSize = functions.getSize();
	for (size_t i = 0; i < containerSize; i++) {
		if (!functions.getFunction(i)->isDefined(x))return false;
	}
	return true;
}
PartialFunction* MinimumFunction::clone() const {
	return new MinimumFunction(*this);
}
