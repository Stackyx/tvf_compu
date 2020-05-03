#pragma once
#include "StocksTerminal.hpp"

class StocksStandardTerminal : public StocksTerminal
{
public:
	StocksStandardTerminal(ContinuousGenerator* gen, double s0, double mu, double maturity);
	
	std::vector<std::vector<std::vector<double>>> Generate(llong n_sims);
};

