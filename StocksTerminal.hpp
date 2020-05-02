#pragma once
#include "Stocks.hpp"
#include "NormalMultiVariate.hpp"

class StocksTerminal : public Stocks
{
public:
	StocksTerminal(ContinuousGenerator* gen, double s0, double mu, double maturity);

	std::vector<std::vector<std::vector<double>>> Generate(llong n_sims) const;
private:
	ContinuousGenerator* Gen;
};

