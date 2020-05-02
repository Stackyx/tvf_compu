#pragma once
#include "Stocks.hpp"
#include "ContinuousGenerator.hpp"

class StocksFullPath : public Stocks
{
public:
	StocksFullPath(ContinuousGenerator* gen, double s0, double mu, double maturity, llong n_steps);
	std::vector<std::vector<std::vector<double>>> Generate(llong n_sims) const;

private:

	ContinuousGenerator* Gen;
	llong N_steps;
};

