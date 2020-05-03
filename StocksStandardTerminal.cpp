#include "StocksStandardTerminal.hpp"
#include "R3R1Function.hpp"
#include <cmath>
#include <iostream>

StocksStandardTerminal::StocksStandardTerminal(ContinuousGenerator* gen, double s0, double mu, double maturity)
	: StocksTerminal(gen, s0, mu, maturity)
{
}

std::vector<std::vector<std::vector<double>>> StocksStandardTerminal::Generate(llong n_sims)
{
	W.resize(n_sims, std::vector<double>(Gen->get_covariance_matrix().size()));
	S.resize(n_sims, std::vector<std::vector<double>>(W[0].size(), std::vector<double>(1)));

	Gen->Generate(W, n_sims);

	for (llong i = 0; i < n_sims; ++i)
	{
		for (llong j = 0; j < W[0].size(); j++)
		{
			S[i][j][0] = S0 * std::exp((Mu - Gen->get_covariance_matrix()[j][j] / 2) * T + std::sqrt(T) * W[i][j]);
		}
	}

	return S;
}