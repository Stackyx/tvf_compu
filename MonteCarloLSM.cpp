#include "MonteCarloLSM.hpp"
#include <algorithm>
#include <numeric>


MonteCarloLSM::MonteCarloLSM(StocksFullPath* stocks, PathDependent* payoff, llong n_sims)
	: MonteCarlo(stocks, payoff, n_sims)
{
}

void MonteCarloLSM::Solve()
{
	std::vector<std::vector<std::vector<double>>> S(mc_stocks->Generate(N_sims));
	std::vector<double> P((*mc_payoff)(S));
	std::vector<double> itm_money(P.size());
	std::vector<double> Weights(mc_payoff->get_weights());
	
	
	price = 0;
	std::cout << "Size = " << P.size() << std::endl;
	
	size_t nb_steps = S[0][0].size();
	double dt = (mc_stocks->get_maturity())/(nb_steps-1);
	double r = mc_stocks->get_mu();
	
	for (int k = nb_steps-2; k>0; k--)
	{
		std::vector<double> X;
		std::vector<double> Y;
		
		for(int i = 0; i<P.size(); ++i)
		{
			if (P[i]>0)
			{
				itm_money[i] = 1;
				double xi = 0;
				for (int j = 0; j<Weights.size(); ++j)
				{
					xi += Weights[j]*S[i][j][k];
				}
				X.push_back(xi);
				Y.push_back(std::exp(-mc_stocks->get_mu() * dt)*P[i]);
			}
			else
			{
				itm_money[i] = 0;
			}
			
			// regression
			
			
		}
	}
	
	
	
	
	
	
	// for (llong i = 0; i < V.size(); i++)
	// {
		// price += V[i] / N_sims;
	// }

	// price *= std::exp(-mc_stocks->get_mu() * mc_stocks->get_maturity());

	// std::cout << "Solving done" << std::endl;
}

// std::vector<std::vector<double>> MonteCarloLSM::get_Ti(const std::vector<std::vector<std::vector<double>>>& S, const int& i)
// {
	// std::vector<st::vector<double>> V_i;
	// V_i.resize(S.size(), std::vector<double>(S[0].size()));
	
	// for (llong l = 0; l<S.size(); l++)
	// {
		// for(int j = 0; j<S[l].size();j++)
		// {
			// V_i[l][j] = S[l][j][i];
		// }
	// }
	// return V_i;
	
// }