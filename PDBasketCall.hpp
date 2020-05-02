#ifndef PDBASKETCALL_HPP
#define PDBASKETCALL_HPP

#include "PDBasket.hpp"

class PDBasketCall :public PDBasket
{
	
public:
	PDBasketCall(double strike, std::vector<double> weights);
	
	std::vector<double> operator()(const std::vector<std::vector<std::vector<double>>>& x) const;
	std::vector<double> operator()(const std::vector<std::vector<std::vector<double>>>& x, const int& k) const;
};

#endif