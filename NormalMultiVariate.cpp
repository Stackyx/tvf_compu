#include "NormalMultiVariate.hpp"
#include <iostream>

NormalMultiVariate::NormalMultiVariate(UniformGenerator* gen, const std::vector<double>& mu,
	const std::vector<std::vector<double>>& cov)
	: Mu(mu), L(cov), Cov(cov)
{
	NormalAlgo type = BoxMuller;
	norm_gen = new Normal(gen, type, 0, 1);
	
	long i, j, k;
	std::vector<double> tmp;
	double sum;
	
	for (i = 0; i < L.size(); i++) {
		for (j = i; j < L.size(); j++) {
			for (sum = L[i][j], k = i - 1; k >= 0; k--) sum -= L[i][k] * L[j][k];
			if (i == j) {
				if (sum <= 0.0)
					throw("Cholesky failed");
				L[i][i] = sqrt(sum);
			}
			else L[j][i] = sum / L[i][i];
		}
	}
	for (i = 0; i < L.size(); i++) for (j = 0; j < i; j++) L[j][i] = 0.;

	for (int i = 0; i < L.size(); i++)
	{
		for (int j = 0; j < L[i].size(); j++)
		{
			std::cout << L[i][j] << ", ";
		}
		std::cout << std::endl;
	}
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
		}
	}

	return Y;
}

std::vector<std::vector<double>> NormalMultiVariate::get_covariance_matrix()
{
	return Cov;
}
