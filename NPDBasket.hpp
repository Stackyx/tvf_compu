#ifndef BASKETPAYOFF_HPP
#define BASKETPAYOFF_HPP

#include "NonPathDependent.hpp"

class NPDBasket :public NonPathDependent
{
	
public:
	NPDBasket(double strike, std::vector<double> weights);

protected:
	std::vector<double> NPD_weights;
	size_t len_weights;
};

#endif