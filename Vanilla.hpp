#ifndef VANILLA_HPP
#define VANILLA_HPP

#include "Payoff.hpp"

class Vanilla :public Payoff
{
	
public:
	Vanilla(double strike);

protected:
	double V_strike;

};

#endif