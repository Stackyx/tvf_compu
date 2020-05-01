#ifndef headTail_HPP
#define headTail_HPP

#include "discrete_generator.hpp"
#include "pseudo_generator.hpp"

class HeadTail : public DiscreteGenerator
{
public:
	HeadTail(UniformGenerator* generator);

	double Generate();
private:
	UniformGenerator* generator;
	double sum;
};

#endif