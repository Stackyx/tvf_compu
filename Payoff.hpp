#ifndef PAYOFF_HPP
#define PAYOFF_HPP

#include <string>
#include <vector>
#include <iostream>

class Payoff
{
public:
	virtual std::vector<double> operator()(std::vector<std::vector<std::vector<double>>> x) = 0;
};

#endif