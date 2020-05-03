#include "EcuyerCombined.hpp"
#include <iostream>

EcuyerCombined::EcuyerCombined(llong seed1, llong seed2)
	: firstGen(new LinearCongruential(40014, 0, 2147483563, seed1)), 
	secondGen(new LinearCongruential(40692, 0, 2147483399, seed2)), x(0.), sum(0.),
	PseudoGenerator(0)
{
}

double EcuyerCombined::Generate()
{
	firstGen->Generate();
	secondGen->Generate();

	x = (long long)firstGen->getCurrent() - (long long)secondGen->getCurrent();

	if (x < 0)
		x += 2147483562;
	
	x = x % 2147483562;

	if (x == 0)
	{
		return 2147483562. / 2147483563.;
	}
	else
	{
		return x / 2147483563.;
	}
}
