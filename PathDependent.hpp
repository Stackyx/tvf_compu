#ifndef PATHDEPENDENT_HPP
#define PATHDEPENDENT_HPP

#include "Payoff.hpp"
class PathDependent : public Payoff
{
	
public:
	PathDependent(double strike);
protected:
	double PD_strike;
};

#endif