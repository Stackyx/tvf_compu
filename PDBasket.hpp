#ifndef PDBASKETPAYOFF_HPP
#define PDBASKETPAYOFF_HPP

#include "PathDependent.hpp"

class PDBasket :public PathDependent
{
	
public:
	PDBasket(double strike, std::vector<double> weights);
	
	virtual std::vector<double> get_weights();
protected:
	std::vector<double> PD_weights;
	size_t len_weights;
};

#endif