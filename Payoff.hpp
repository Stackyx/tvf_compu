#ifndef PAYOFF_HPP
#define PAYOFF_HPP

#include <string>
#include <vector>
#include <iostream>

class Payoff
{
public:
	virtual std::vector<double> operator()(const std::vector<std::vector<std::vector<double>>>& x) const = 0;
	virtual std::vector<double> get_weights() = 0;
};

#endif