#pragma once
#include "Stocks.hpp"
#include "NormalMultiVariate.hpp"

class StocksTerminal : public Stocks
{
public:
	StocksTerminal(ContinuousGenerator* gen, double s0, const std::vector<double>& mu, double maturity);

	std::vector<double> Generate();
	std::vector<std::vector<std::vector<double>>> Generate(llong n_sims);
private:

	ContinuousGenerator* Gen;

	double S0, T;

	const std::vector<double>& Mu;
};

