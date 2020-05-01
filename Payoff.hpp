#ifndef PAYOFF_HPP
#define PAYOFF_HPP
#include <string>
#include <vector>
#include <iostream>
class Payoff
{
	
public:
	Payoff();
	~Payoff();
	
	virtual double operator()(std::vector<double> x) = 0;
	virtual double operator()(double x) = 0;
};

#endif