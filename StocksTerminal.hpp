#pragma once
#include "Stocks.hpp"

class StocksTerminal : public Stocks
{
public:
	StocksTerminal(ContinuousGenerator* Gen, double s0, double mu, double maturity);
};

