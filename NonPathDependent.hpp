#ifndef NONPATHDEPENDENT_HPP
#define NONPATHDEPENDENT_HPP

#include "Payoff.hpp"
class NonPathDependent : public Payoff
{
	
public:
	NonPathDependent();
	NonPathDependent(double strike);
	
protected:
	double NPD_strike;
};

#endif