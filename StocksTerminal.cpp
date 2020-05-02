#include "StocksTerminal.hpp"
#include <cmath>

StocksTerminal::StocksTerminal(ContinuousGenerator* gen, double s0, double mu, double maturity)
	: Stocks(s0, mu, maturity), Gen(gen)
{
}

std::vector<std::vector<std::vector<double>>> StocksTerminal::Generate(llong n_sims) const
{
	std::vector<std::vector<double>> W(Gen->Generate(n_sims));
	std::vector<std::vector<std::vector<double>>> S(n_sims, std::vector<std::vector<double>>(W[0].size(), std::vector<double>(1)));

	for (llong i = 0; i < n_sims; ++i)
	{
		for (llong j = 0; j < W[0].size(); j++)
		{
			S[i][j][0] = S0 * std::exp((Mu - Gen->get_covariance_matrix()[j][j] / 2) * T + std::sqrt(T) * W[i][j]);
		}
	}

	return S;
}
