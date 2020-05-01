#ifndef EXOTIC_HPP
#define EXOTIC_HPP

#include "Payoff.hpp"

class Exotic :public Payoff
{
	
public:
	Exotic(double strike);
	
protected:
	double E_strike;

};

#endif