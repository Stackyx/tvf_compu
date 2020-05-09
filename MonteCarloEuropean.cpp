#include "MonteCarloEuropean.hpp"
#include "Tools.hpp"

MonteCarloEuropean::MonteCarloEuropean(StocksTerminal* stocks, NonPathDependent* payoff, llong n_sims)
	: MonteCarlo(stocks, payoff, n_sims)
{
}

MonteCarloEuropean::MonteCarloEuropean(StocksFullPath* stocks, PathDependent* payoff, llong n_sims)
	: MonteCarlo(stocks, payoff, n_sims)
{
}

MonteCarloEuropean::MonteCarloEuropean(StocksTerminal* stocks, NonPathDependent* payoff, llong n_sims, NonPathDependent* payoff_CV, double closedFormValue)
	: MonteCarlo(stocks, payoff, n_sims, payoff_CV, closedFormValue)
{
}

MonteCarloEuropean::MonteCarloEuropean(StocksFullPath* stocks, PathDependent* payoff, llong n_sims, PathDependent* payoff_CV, double closedFormValue)
	: MonteCarlo(stocks, payoff, n_sims, payoff_CV, closedFormValue)
{
}

void MonteCarloEuropean::Solve()
{
	std::vector<std::vector<std::vector<double>>> S(mc_stocks->Generate(N_sims));
	
	std::vector<double> V((*mc_payoff)(S));
	std::vector<double> V_CV((*MC_payoff_CV)(S));

	price = 0;
	double price2 = 0;
	
	for (llong i = 0; i < V.size(); i++)
	{
		price += V[i] / V.size();
		std::cout<<"price "<< V[i]<<", spot "<<S[i][0][S[0][0].size()-1]*0.5 + 0.5 * S[i][1][S[0][0].size()-1]<<std::endl;
		price2 += V_CV[i] / V_CV.size();
	}

	price *= std::exp(-mc_stocks->get_mu() * mc_stocks->get_maturity());
	price2 *= std::exp(-mc_stocks->get_mu() * mc_stocks->get_maturity());
	
	price = price + (closedFormValue - price2);
}


