#ifndef NPDBASKETPUT_HPP
#define NPDBASKETPUT_HPP

#include "NPDBasket.hpp"

class NPDBasketPut :public NPDBasket
{
	
public:
	NPDBasketPut(double strike, std::vector<double> weights);
	
	std::vector<double> operator()(const std::vector<std::vector<std::vector<double>>>& x) const;
};

#endif