#pragma once
#include "MonteCarlo.hpp"

// This class can price payoffs with exercise at maturity only

// INPUTS : Terminal value assets and non path dependent payoff with llong n simulations
//			Full path value assets and path dependent payoff with llong n simulations

class MonteCarloEuropean : public MonteCarlo
{
public:
	MonteCarloEuropean(StocksTerminal* stocks, NonPathDependent* payoff, llong n_sims);
	MonteCarloEuropean(StocksFullPath* stocks, PathDependent* payoff, llong n_sims);
	
	MonteCarloEuropean(StocksTerminal* stocks, NonPathDependent* payoff, llong n_sims, NonPathDependent* payoff_CV, double closedFormValue);
	MonteCarloEuropean(StocksFullPath* stocks, PathDependent* payoff, llong n_sims, PathDependent* payoff_CV, double closedFormValue);

	void Solve();
};

