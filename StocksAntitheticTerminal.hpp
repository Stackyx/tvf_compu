#pragma once
#include "StocksTerminal.hpp"


// This instantiable class can generate final value of assets prices implementing the Antithetic variance reduction method.

// INPUTS : Continuous random number generator, double S0, double risk free rate, double maturity, function to apply the antithetic transformation to the brownians

class StocksAntitheticTerminal : public StocksTerminal
{
public:
	StocksAntitheticTerminal(ContinuousGenerator* gen, double s0, double mu, double maturity, R3R1Function* Transform);

	std::vector<std::vector<std::vector<double>>> Generate(llong n_sims);
private:
	R3R1Function* Transform;
	std::vector<std::vector<double>> W_transform;
};

