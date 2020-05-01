#pragma once
#include "Stocks.hpp"
#include "ContinuousGenerator.hpp"

class StocksFullPath : public Stocks
{
public:
	StocksFullPath(ContinuousGenerator* gen, const std::vector<double>& s0, const std::vector<double>& mu, double maturity, llong n_steps);
	std::vector<std::vector<std::vector<double>>> Generate(llong n_sims);

private:

	ContinuousGenerator* Gen;
	llong N_steps;
	double T;

	const std::vector<double>& Mu, S0;


};

