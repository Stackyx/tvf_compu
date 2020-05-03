#include "NormalMultiVariate.hpp"
#include <iostream>
#include "Tools.hpp"

NormalMultiVariate::NormalMultiVariate(UniformGenerator* gen, const std::vector<double>& mu, const std::vector<std::vector<double>>& cov)
	: Mu(mu), L(cov), Cov(cov)
{
	if (Mu.size() != Cov.size())
	{
		throw std::runtime_error("Size of the Mu vector must coincide with Cov size.");
	}

	NormalAlgo type = BoxMuller;
	norm_gen = new Normal(gen, type, 0, 1);
	
	Cholesky(L);
}

NormalMultiVariate::NormalMultiVariate(UniformGenerator* gen1, UniformGenerator* gen2, const std::vector<double>& mu, const std::vector<std::vector<double>>& cov)
	: Mu(mu), L(cov), Cov(cov)
{
	if (Mu.size() != Cov.size())
	{
		throw std::runtime_error("Size of the Mu vector must coincide with Cov size.");
	}

	norm_gen = new Normal(gen1, gen2, 0, 1);

	Cholesky(L);
}

NormalMultiVariate::NormalMultiVariate(UniformGenerator* gen, double mu, const std::vector<std::vector<double>>& cov)
	: L(cov), Cov(cov)
{
	Mu.resize(Cov.size());
	for (llong i = 0; i < Mu.size(); ++i)
	{
		Mu[i] = mu;
	}

	NormalAlgo type = BoxMuller;
	norm_gen = new Normal(gen, type, 0, 1);

	Cholesky(L);
}

NormalMultiVariate::NormalMultiVariate(UniformGenerator* gen1, UniformGenerator* gen2, double mu, const std::vector<std::vector<double>>& cov)
	: Mu(mu), L(cov), Cov(cov)
{
	Mu.resize(Cov.size());
	for (llong i = 0; i < Mu.size(); ++i)
	{
		Mu[i] = mu;
	}

	norm_gen = new Normal(gen1, gen2, 0, 1);

	Cholesky(L);
}

double NormalMultiVariate::Generate()
{
	throw std::runtime_error("Can't use this method for multivariate.");
	return 0;
}

std::vector<std::vector<double>> NormalMultiVariate::Generate(llong n)
{
	llong s(L.size());
	std::vector<double> X(s);
	std::vector<std::vector<double>> Y(n, std::vector<double>(s));

	for (llong z = 0; z < n; ++z)
	{
		for (llong i = 0; i < s; ++i)
		{
			X[i] = norm_gen->Generate();
		}

		for (llong i = 0; i < s; ++i)
		{
			Y[z][i] = 0;
			for (llong j = 0; j < s; ++j)
			{
				Y[z][i] += L[i][j] * X[j];
			}
			Y[z][i] += Mu[i];
		}
	}

	return Y;
}

std::vector<std::vector<double>> NormalMultiVariate::get_covariance_matrix()
{
	return Cov;
}
