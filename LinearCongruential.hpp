#ifndef LINEAR_CONGRUENTIAL
#define LINEAR_CONGRUENTIAL

#include "pseudo_generator.hpp"

class LinearCongruential : public PseudoGenerator
{
public:
	LinearCongruential(llong m, llong i, llong mod, llong seed);
	
	double Generate();

	long get_mod() const;
private:

	llong x = 0;
	llong multiplier;
	llong increment;
	llong modulus;
	double sum = 0;
};

#endif