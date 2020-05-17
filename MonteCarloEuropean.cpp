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
	
	std::vector<double> V((*mc_payoff)(S)); // Compute the payoff at time T of each simulation
	std::vector<double> V_CV((*MC_payoff_CV)(S));

	price = 0;
	double price2 = 0;
	
	price = std::accumulate(V.begin(), V.end(), 0.0)/(V.size());
	price2 = std::accumulate(V_CV.begin(), V_CV.end(), 0.0)/(V_CV.size()); // Use in cunjonction of the Control Variate variance reduction method.

	price *= std::exp(-mc_stocks->get_mu() * mc_stocks->get_maturity());
	price2 *= std::exp(-mc_stocks->get_mu() * mc_stocks->get_maturity());
	
	price = price + (closedFormValue - price2);
}


