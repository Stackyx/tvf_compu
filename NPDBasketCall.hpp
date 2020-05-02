#ifndef NPDBASKETCALL_HPP
#define NPDBASKETCALL_HPP

#include "NPDBasket.hpp"

class NPDBasketCall :public NPDBasket
{
	
public:
	NPDBasketCall(double strike, std::vector<double> weights);
	
	std::vector<double> operator()(const std::vector<std::vector<std::vector<double>>>& x) const;

};

#endif