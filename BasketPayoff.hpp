#ifndef BASKETPAYOFF_HPP
#define BASKETPAYOFF_HPP

#include "Exotic.hpp"

class BasketPayoff :public Exotic
{
	
public:
	BasketPayoff(double strike, std::vector<double> weights);

protected:
	std::vector<double> E_weights;
	size_t len_weights;
};

#endif