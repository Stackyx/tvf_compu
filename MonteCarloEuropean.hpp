#pragma once
#include "MonteCarlo.hpp"

class MonteCarloEuropean : public MonteCarlo
{
public:
	MonteCarloEuropean(StocksTerminal* stocks, NonPathDependent* payoff, llong n_sims);
	MonteCarloEuropean(StocksFullPath* stocks, PathDependent* payoff, llong n_sims);
	
	MonteCarloEuropean(StocksTerminal* stocks, NonPathDependent* payoff, llong n_sims, NonPathDependent* payoff_CV, double closedFormValue);
	MonteCarloEuropean(StocksFullPath* stocks, PathDependent* payoff, llong n_sims, PathDependent* payoff_CV, double closedFormValue);

	void Solve();
};

