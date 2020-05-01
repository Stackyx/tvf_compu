#ifndef BASKETCALL_HPP
#define BASKETCALL_HPP

#include "BasketPayoff.hpp"

class BasketCall :public BasketPayoff
{
	
public:
	BasketCall(double strike, std::vector<double> weights);
	
	
	double operator()(double x);
	virtual double operator()(std::vector<double> x);

};

#endif