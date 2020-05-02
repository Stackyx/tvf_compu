#include "StocksFullPath.hpp"
#include <cmath>

StocksFullPath::StocksFullPath(ContinuousGenerator* gen, double s0, double mu, double maturity, llong n_steps)
	: Stocks(gen, s0, mu, maturity), N_steps(n_steps)
{

}

std::vector<std::vector<std::vector<double>>> StocksFullPath::Generate(llong n_sims) const
{
	std::vector<std::vector<double>> W(Gen->Generate(n_sims));
	std::vector<std::vector<std::vector<double>>> S(n_sims, std::vector<std::vector<double>>(W[0].size(), std::vector<double>(N_steps)));

	double dt = T / (N_steps - 1);

	for (llong i = 0; i < n_sims; ++i)
	{
		for (llong j=0; j<W[0].size();++j)
		{
			S[i][j][0] = std::log(S0);
		}
	}

	for (llong z = 1; z < N_steps; ++z)
	{
		W = Gen->Generate(n_sims);
		for (llong i = 0; i < n_sims; ++i)
		{
			for (llong j = 0; j < W[0].size(); j++)
			{
				S[i][j][z] = S[i][j][z-1] + (Mu - 1 / 2 * Gen->get_covariance_matrix()[j][j]) * dt + std::sqrt(dt) * W[i][j];
			}
		}
	}

	for (llong i = 0; i < n_sims; ++i)
	{
		for (llong j = 0; j < W[0].size(); ++j)
		{
			for (llong z = 0; z < N_steps; ++z)
			{
				S[i][j][z] = std::exp(S[i][j][z]);
			}
		}
	}

	return S;
}
