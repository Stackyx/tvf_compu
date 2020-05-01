#ifndef PSEUDO_GENERATOR_HPP
#define PSEUDO_GENERATOR_HPP

#include "uniform_generator.hpp"

class PseudoGenerator : public UniformGenerator
{
public:
	PseudoGenerator();
	PseudoGenerator(llong s);
	~PseudoGenerator();

protected:
	llong seed;
};

#endif