#ifndef ECUYER_COMBINED_HPP
#define ECUYER_COMBINED_HPP

#include "pseudo_generator.hpp"
#include "LinearCongruential.h"

class EcuyerCombined : public PseudoGenerator
{
public:

	EcuyerCombined(llong seed1, llong seed2);
	double Generate();

private:
	PseudoGenerator* firstGen;
	PseudoGenerator* secondGen;

	double sum;
	long long x;
};

#endif