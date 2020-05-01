#include "StocksTerminal.hpp"
#include <cmath>

StocksTerminal::StocksTerminal(ContinuousGenerator* gen, double s0, const std::vector<double>& mu, double maturity)
	: Gen(gen), S0(s0), Mu(mu), T(maturity)
{
}

std::vector<double> StocksTerminal::Generate()
{
	std::vector<std::vector<double>> W(Gen->Generate(1));
	std::vector<double> S(W[0].size());

	for (llong i = 0; i < W[0].size(); i++)
	{
		S[i] = S0 * std::exp((Mu[i]-Gen->get_covariance_matrix()[i][i]/2)*T + std::sqrt(T) * W[0][i]);
	}

	return S;
}

std::vector<std::vector<std::vector<double>>> StocksTerminal::Generate(llong n_sims)
{
	std::vector<std::vector<double>> W(Gen->Generate(n_sims));
	std::vector<std::vector<std::vector<double>>> S(n_sims, std::vector<std::vector<double>>(W[0].size(), std::vector<double>(1)));

	for (llong i = 0; i < n_sims; ++i)
	{
		for (llong j = 0; j < W[0].size(); j++)
		{
			S[i][j][0] = S0 * std::exp((Mu[j] - Gen->get_covariance_matrix()[j][j] / 2) * T + std::sqrt(T) * W[i][j]);
		}
	}

	return S;
}
