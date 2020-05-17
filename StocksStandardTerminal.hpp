#pragma once
#include "StocksTerminal.hpp"

// This instantiable class can generate final value of assets prices.

// INPUTS : Continuous random number generator, double S0, double risk free rate, double maturity

class StocksStandardTerminal : public StocksTerminal
{
public:
	StocksStandardTerminal(ContinuousGenerator* gen, double s0, double mu, double maturity);
	
	std::vector<std::vector<std::vector<double>>> Generate(llong n_sims);
};

