#define _USE_MATH_DEFINES
#include "Normal.h"
#include "Exponential.h"
#include "head_tail.hpp"
#include <iostream>
#include <cmath>

Normal::Normal(UniformGenerator* gen, NormalAlgo type, double mu, double sigma)
	: type(type), mu(mu), sigma(std::sqrt(sigma)), gen(gen)
{
	AlgoType typeexp = InverseDist;
	switch (type)
	{
	case BoxMuller:
		break;
	case CLT:
		break;
	case N_RejectionSamp:
		exp_gen = new Exponential(gen, typeexp, 1);
		ht_gen = new HeadTail(gen);
		break;
	default:
		throw std::runtime_error("Insert proper algo type");
		break;
	}
}

double Normal::Generate()
{
	switch (type)
	{
	case BoxMuller:
		if (isGenerated)
		{
			isGenerated = false;
			return mu+sigma*x;
		}
		else
		{
			
			y = std::sqrt(-2 * std::log(gen->Generate()));
			z = 2 * M_PI * gen->Generate();
			x = y * std::sin(z);

			isGenerated = true;

			return mu + sigma*(y * std::cos(z));
		}
		break;
	case CLT:
		
		x = 0;
		for (int i = 0; i < 12; ++i)
		{
			x += gen->Generate();
		}
		return sigma*(x - 6) + mu;

		break;
	case N_RejectionSamp:
		x = exp_gen->Generate() * ht_gen->Generate();
		y = std::sqrt(2 * M_E / M_PI) * 1./2. * std::exp(-std::abs(x)) * gen->Generate();
		while (y > std::exp(-x * x / 2.) / std::sqrt(2 * M_PI))
		{
			x = exp_gen->Generate() * ht_gen->Generate();
			y = std::sqrt(2 * M_E / M_PI) * 1. / 2. * std::exp(-std::abs(x)) * gen->Generate();
		}
		return x;
		break;
	default:
		throw std::runtime_error("Insert valid method");
		break;
	}
}
