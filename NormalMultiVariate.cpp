#include "NormalMultiVariate.hpp"
#include <iostream>

NormalMultiVariate::NormalMultiVariate(UniformGenerator* gen, std::vector<double> mu, std::vector<double> sigma, double corr)
	: gen(gen), corr(corr), mu(mu), sigma(sigma)
{
	NormalAlgo type = BoxMuller;
	norm_gen = new Normal(gen, type, 0, 1);
}

NormalMultiVariate::NormalMultiVariate(UniformGenerator* gen, std::vector<double> mu,
	std::vector<double> sigma,
	std::vector<std::vector<double>> corr)
{
	throw std::runtime_error("Multivariate not implemented");
}

double NormalMultiVariate::Generate()
{
	throw std::runtime_error("Can't use this method for multivariate.");
	return 0;
}

std::vector<double> NormalMultiVariate::Generate(llong n)
{
	std::vector<double> r;
	double x1;
	for (llong j = 0; j < n; ++j)
	{
		for (llong i = 0; i < mu.size(); ++i)
		{
			x1 = norm_gen->Generate();
			r.push_back(mu[i] + sigma[i] * x1);
			r.push_back(mu[i+1] + sigma[i+1]*(corr*x1 + std::sqrt(1-corr*corr)*norm_gen->Generate()));
		}
	}

	return r;
}
