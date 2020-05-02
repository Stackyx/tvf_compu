#pragma once
#include "Stocks.hpp"
#include "NormalMultiVariate.hpp"

class StocksTerminal : public Stocks
{
public:
	StocksTerminal(ContinuousGenerator* gen, double s0, double mu, double maturity);

	std::vector<std::vector<std::vector<double>>> Generate(llong n_sims) const;
	std::vector<std::vector<std::vector<double>>> Generate(llong n_sims, R3R1Function* Transform) const;
private:
	ContinuousGenerator* Gen;
};

