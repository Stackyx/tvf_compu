#ifndef PAYOFF_HPP
#define PAYOFF_HPP

#include <string>
#include <vector>
#include <iostream>

typedef unsigned long long llong;

class Payoff
{
public:
	virtual std::vector<double> operator()(const std::vector<std::vector<std::vector<double>>>& x) const = 0;

	virtual std::vector<double> get_weights();
	virtual std::vector<double> operator()(const std::vector<std::vector<std::vector<double>>>& x, const int& k) const;
};

#endif