#ifndef Exponential_HPP
#define Exponential_HPP


#include "ContinuousGenerator.h"
#include "uniform_generator.hpp"

enum AlgoType {
	InverseDist,
	RejectionSamp
};

class Exponential : public ContinuousGenerator
{
public:

	Exponential(UniformGenerator* gen, AlgoType type, double lambda);
	double Generate();

private:
	UniformGenerator* gen;
	AlgoType type;
	double lambda;
};

#endif