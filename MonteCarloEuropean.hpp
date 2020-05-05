#pragma once
#include "MonteCarlo.hpp"

class MonteCarloEuropean : public MonteCarlo
{
public:
	MonteCarloEuropean(StocksTerminal* stocks, NonPathDependent* payoff, llong n_sims);
	MonteCarloEuropean(StocksFullPath* stocks, PathDependent* payoff, llong n_sims);

	void Solve();
	void Solve(Payoff* MC_payoff_CV, double ClosedFormValue);
	
};

