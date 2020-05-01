#include "LinearCongruential.hpp"
#include "iostream"

LinearCongruential::LinearCongruential(llong m, llong i, llong mod, llong seed)
	: multiplier(m), increment(i), modulus(mod),
	PseudoGenerator(seed)
{
}

double LinearCongruential::Generate()
{
	current = (multiplier * current + increment) % modulus;
	return current/(modulus - 1);
}

long LinearCongruential::get_mod() const 
{
	return modulus;
}
