#include "StocksAntitheticFullPath.hpp"
#include <cmath>
#include <iostream>
StocksAntitheticFullPath::StocksAntitheticFullPath(ContinuousGenerator* gen, double s0, double mu, double maturity, llong n_steps, R3R1Function* Transform)
	: StocksFullPath(gen, s0, mu, maturity, n_steps), Transform(Transform)
{
}

StocksAntitheticFullPath::StocksAntitheticFullPath(ContinuousGenerator* gen, double s0, double mu, double maturity, R3R1Function* Transform, const std::vector<double>& dividends, const std::vector<double>& date_dividends, llong n_steps)
	: StocksFullPath(gen, s0, mu, maturity, dividends, date_dividends, n_steps), Transform(Transform)
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
	llong cpt_div = 0;
	double divVal = 0;
	llong cpt(0);

	for (llong i = 0; i < n_sims*2; ++i)
	{
		for (llong j = 0; j < W[0].size(); ++j)
		{

			S[i][j][0] = S0;
		}
	}

	for (llong z = 1; z < N_steps; ++z)
	{
		W = Gen->Generate(n_sims);
		W_transform = (*Transform)(W, 0, 1); // Apply the antithetic transformation

		// This blocks handle by the exact same method the dividends payment.

		if (z * dt < Date_Div[cpt_div] && Date_Div[cpt_div] <= (z + 1) * dt)
		{
			divVal = Div[cpt_div];

			if (cpt_div < Div.size()-1)
			{
				cpt_div += 1;
			}
		}

		cpt = 0;
		for (llong i = 0; i < n_sims*2-1; i+=2)
		{
			for (llong j = 0; j < W[0].size(); j++)
			{
				S[i][j][z] = S[i][j][z - 1] + S[i][j][z - 1] * ((Mu)*dt + std::sqrt(dt) * W[cpt][j]) - divVal;
				S[i+1][j][z] = S[i+1][j][z - 1] + S[i+1][j][z - 1] * ((Mu)*dt + std::sqrt(dt) * W_transform[cpt][j]) - divVal;
			}
			cpt += 1;
		}
		divVal = 0;
	}


	return S;
}

