#ifndef UNIFORM_GENERATOR_HPP
#define UNIFORM_GENERATOR_HPP

#include "random_generator.hpp"

class UniformGenerator : public RandomGenerator
{
public:
	UniformGenerator(llong seed);
protected:
	llong s;
};

#endif