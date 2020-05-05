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

void MonteCarloEuropean::Solve(Payoff* MC_payoff_CV, double ClosedFormValue)
{
	std::vector<std::vector<std::vector<double>>> S(mc_stocks->Generate(N_sims));
	std::vector<double> V((*mc_payoff)(S));
	std::vector<double> V_CV((*MC_payoff_CV)(S));

	price = 0;
	double price2 = 0;
	
	for (llong i = 0; i < V.size(); i++)
	{
		price += V[i] / V.size();
		price2 += V_CV[i] / V_CV.size();
	}

	price *= std::exp(-mc_stocks->get_mu() * mc_stocks->get_maturity());
	price2 *= std::exp(-mc_stocks->get_mu() * mc_stocks->get_maturity());
	
	price = price + (ClosedFormValue - price2);
}


