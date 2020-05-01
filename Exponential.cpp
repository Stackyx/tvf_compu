#include "Exponential.h"
#include "cmath"
#include <iostream>

Exponential::Exponential(UniformGenerator* gen, AlgoType type, double lambda)
	: lambda(lambda), gen(gen), type(type)
{
}

double Exponential::Generate()
{
	double x = gen->Generate();
	switch (type)
	{
	case InverseDist:
		return -std::log(x) / lambda;
		break;
	case RejectionSamp:
		throw std::runtime_error("Not implemented yet.");

		break;
	default:
		break;
	}
}