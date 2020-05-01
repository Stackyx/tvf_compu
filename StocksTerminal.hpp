#pragma once
#include "Stocks.hpp"
#include "NormalMultiVariate.hpp"

class StocksTerminal : public Stocks
{
public:
	StocksTerminal(ContinuousGenerator* gen, const std::vector<double>& s0, const std::vector<double>& mu, double maturity);

	std::vector<std::vector<std::vector<double>>> Generate(llong n_sims);
private:

	ContinuousGenerator* Gen;

	double T;
	const std::vector<double>& Mu, S0;
};

