#ifndef PATHDEPENDENT_HPP
#define PATHDEPENDENT_HPP

#include "Payoff.hpp"
class PathDependent : public Payoff
{
	
public:
	PathDependent(double strike);
	
	virtual std::vector<double> operator()(const std::vector<std::vector<std::vector<double>>>& x, const int& k) const = 0;
protected:
	double PD_strike;
};

#endif