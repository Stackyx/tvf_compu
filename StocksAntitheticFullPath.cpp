#include "StocksAntitheticFullPath.hpp"
#include <cmath>
StocksAntitheticFullPath::StocksAntitheticFullPath(ContinuousGenerator* gen, double s0, double mu, double maturity, llong n_steps, R3R1Function* Transform)
	: StocksFullPath(gen, s0, mu, maturity, n_steps), Transform(Transform)
{
}

std::vector<std::vector<std::vector<double>>> StocksAntitheticFullPath::Generate(llong n_sims)
{
	W.resize(n_sims, std::vector<double>(Gen->get_covariance_matrix().size()));
	W_transform.resize(n_sims, std::vector<double>(Gen->get_covariance_matrix().size()));

	Gen->Generate(W, n_sims);
	(*Transform)(W_transform, W, 0, 1);

	S.resize(n_sims*2, std::vector<std::vector<double>>(W[0].size(), std::vector<double>(N_steps)));

	double dt = T / (N_steps - 1);
	llong cpt(0);

	for (llong i = 0; i < n_sims*2; ++i)
	{
		for (llong j = 0; j < W[0].size(); ++j)
		{
			S[i][j][0] = std::log(S0);
		}
	}

	for (llong z = 1; z < N_steps; ++z)
	{
		W = Gen->Generate(n_sims);
		W_transform = (*Transform)(W, 0, 1);

		cpt = 0;
		for (llong i = 0; i < n_sims*2-1; ++i)
		{
			for (llong j = 0; j < W[0].size(); j++)
			{
				S[i][j][z] = S[i][j][z - 1] + (Mu - 1 / 2 * Gen->get_covariance_matrix()[j][j]) * dt + std::sqrt(dt) * W[cpt][j];
				S[i+1][j][z] = S[i][j][z - 1] + (Mu - 1 / 2 * Gen->get_covariance_matrix()[j][j]) * dt + std::sqrt(dt) * W_transform[cpt][j];
			}
			cpt += 1;
		}
	}

	for (llong i = 0; i < n_sims*2; ++i)
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

