#include "MonteCarloEuropean.hpp"

MonteCarloEuropean::MonteCarloEuropean(StocksTerminal* stocks, NonPathDependent* payoff, llong n_sims)
	: MonteCarlo(stocks, payoff, n_sims)
{
}

MonteCarloEuropean::MonteCarloEuropean(StocksFullPath* stocks, PathDependent* payoff, llong n_sims)
	: MonteCarlo(stocks, payoff, n_sims)
{
}

void MonteCarloEuropean::Solve()
{
	std::vector<std::vector<std::vector<double>>> S(mc_stocks->Generate(N_sims));
	std::vector<double> V((*mc_payoff)(S));

	price = 0;

	for (llong i = 0; i < V.size(); i++)
	{
		price += V[i] / V.size();
	}

	price *= std::exp(-mc_stocks->get_mu() * mc_stocks->get_maturity());
}
