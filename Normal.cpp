#define _USE_MATH_DEFINES
#include "Normal.hpp"
#include "Exponential.hpp"
#include "head_tail.hpp"
#include "VanDerCorput.hpp"
#include <iostream>
#include <cmath>

Normal::Normal(UniformGenerator* gen, NormalAlgo type, double mu, double sigma)
	: type(type), mu(mu), sigma(std::sqrt(sigma)), gen1(gen), gen2(gen), x(0), y(0)
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

Normal::Normal(UniformGenerator* gen, UniformGenerator* gen2, double mu, double sigma)
	: mu(mu), sigma(std::sqrt(sigma)), gen1(gen), gen2(gen2), type(BoxMuller)
{
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
			double r = std::sqrt(-2 * std::log(gen1->Generate()));
			double theta = 2 * M_PI * gen2->Generate();
			x = r * std::cos(theta);

			isGenerated = true;

			return mu + sigma*(r * std::sin(theta));
		}
		break;
	case CLT:
		
		x = 0;
		for (int i = 0; i < 12; ++i)
		{
			x += gen1->Generate();
		}
		return sigma*(x - 6) + mu;

		break;
	case N_RejectionSamp:
		x = exp_gen->Generate() * ht_gen->Generate();
		y = std::sqrt(2 * M_E / M_PI) * 1./2. * std::exp(-std::abs(x)) * gen1->Generate();
		while (y > std::exp(-x * x / 2.) / std::sqrt(2 * M_PI))
		{
			x = exp_gen->Generate() * ht_gen->Generate();
			y = std::sqrt(2 * M_E / M_PI) * 1. / 2. * std::exp(-std::abs(x)) * gen1->Generate();
		}
		return x;
		break;
	default:
		throw std::runtime_error("Insert valid method");
		break;
	}
}
