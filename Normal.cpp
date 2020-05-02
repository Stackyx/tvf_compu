#define _USE_MATH_DEFINES
#include "Normal.hpp"
#include "Exponential.hpp"
#include "head_tail.hpp"
#include "VanDerCorput.hpp"
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
			double r = std::sqrt(-2 * std::log(gen->Generate()));
			double theta = 2 * M_PI * gen->Generate();
			x = r * std::cos(theta);

			isGenerated = true;

			return mu + sigma*(r * std::sin(theta));
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
