#include "StocksAntitheticTerminal.hpp"
#include <cmath>

StocksAntitheticTerminal::StocksAntitheticTerminal(ContinuousGenerator* gen, double s0, double mu, double maturity, R3R1Function* Transform)
	: StocksTerminal(gen, s0, mu, maturity), Transform(Transform)
{
}

std::vector<std::vector<std::vector<double>>> StocksAntitheticTerminal::Generate(llong n_sims) const
{
	std::vector<std::vector<double>> W(Gen->Generate(n_sims));
	std::vector<std::vector<double>> W_transform((*Transform)(W, 0, 1));

	std::vector<std::vector<std::vector<double>>> S(n_sims * 2, std::vector<std::vector<double>>(W[0].size(), std::vector<double>(1)));

	llong cpt = 0;

	for (llong i = 0; i < n_sims * 2 - 1; i += 2)
	{
		for (llong j = 0; j < W[0].size(); j++)
		{
			S[i][j][0] = S0 * std::exp((Mu - Gen->get_covariance_matrix()[j][j] / 2) * T + std::sqrt(T) * W[cpt][j]);
			S[i + 1][j][0] = S0 * std::exp((Mu - Gen->get_covariance_matrix()[j][j] / 2) * T + std::sqrt(T) * W_transform[cpt][j]);
		}
		cpt += 1;
	}

	return S;
}
