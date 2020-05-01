#ifndef BASKETPUT_HPP
#define BASKETPUT_HPP

#include "BasketPayoff.hpp"

class BasketPut :public BasketPayoff
{
	
public:
	BasketPut(double strike, std::vector<double> weights);
	
	
	double operator()(double x);
	virtual double operator()(std::vector<double> x);

};

#endif