#ifndef PDBASKETCALL_HPP
#define PDBASKETCALL_HPP

#include "PDBasket.hpp"

class PDBasketCall :public PDBasket
{
	
public:
	PDBasketCall(double strike, std::vector<double> weights);
	
	virtual std::vector<double> operator()(const std::vector<std::vector<std::vector<double>>>& x) const;
	virtual std::vector<double> operator()(const std::vector<std::vector<std::vector<double>>>& x, const int& k);
};

#endif