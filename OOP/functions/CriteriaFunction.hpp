#pragma once
#include "PartialFunction.h"
template<typename Function>
class CriteriaFunction : public PartialFunction {
public:
	CriteriaFunction() {}
	CriteriaFunction(const Function& newFunction);
	Pair<int32_t, int32_t> operator()(int32_t x) const override;
	bool isDefined(int32_t x) const override;
	PartialFunction* clone() const override;
	void setFunction(const Function& function);
private:
	Function func;
};
template<typename Function>
CriteriaFunction<Function>::CriteriaFunction(const Function& newFunction) {
	func = newFunction;
}
template<typename Function>
inline Pair<int32_t, int32_t> CriteriaFunction<Function>::operator()(int32_t x) const
{
	if (isDefined(x)) {
		Pair<int32_t, int32_t> pair(x, func(x));
		return pair;
	}
		throw std::logic_error("Point is undefined!");
	
}

template<typename Function>
inline bool CriteriaFunction<Function>::isDefined(int32_t x) const
{
	for (int i = 0;i < this->size;i++) {
		if (this->defined_points[i].getX() == x) {
			return this->defined_points[i].getY();
		}
	}
	return true;
	
}

template<typename Function>
inline PartialFunction* CriteriaFunction<Function>::clone() const
{
	return new CriteriaFunction<Function>(*this);
}
template<typename Function>
void CriteriaFunction<Function>::setFunction(const Function& function) {
	func = function;
}