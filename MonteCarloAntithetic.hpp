#pragma once
#include "MonteCarlo.hpp"
#include "R3R1Function.hpp"

class MonteCarloAntithetic : public MonteCarlo
{
public:
	MonteCarloAntithetic(StocksTerminal* stocks, NonPathDependent* payoff, R3R1Function* Transform, llong n_sims);
	void Solve();
private:
	R3R1Function* AntitheticTransform;
};

