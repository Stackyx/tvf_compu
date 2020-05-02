#pragma once
#include "StocksTerminal.hpp"

class StocksAntitheticTerminal : public StocksTerminal
{
public:
	StocksAntitheticTerminal(ContinuousGenerator* gen, double s0, double mu, double maturity, R3R1Function* Transform);

	std::vector<std::vector<std::vector<double>>> Generate(llong n_sims) const;
private:
	R3R1Function* Transform;
};

