#include "MonteCarloAntithetic.hpp"

MonteCarloAntithetic::MonteCarloAntithetic(StocksTerminal* stocks, NonPathDependent* payoff, R3R1Function* Transform, llong n_sims)
	: MonteCarlo(stocks, payoff, n_sims), AntitheticTransform(Transform)
{
}

void MonteCarloAntithetic::Solve()
{
	std::vector<std::vector<std::vector<double>>> S(mc_stocks->Generate(N_sims, AntitheticTransform));
	std::vector<double> V((*mc_payoff)(S));

	price = 0;

	for (llong i = 0; i < V.size(); i++)
	{
		price += V[i] / V.size();
	}

	price *= std::exp(-mc_stocks->get_mu() * mc_stocks->get_maturity());

	std::cout << "Done solving." << std::endl;
}
