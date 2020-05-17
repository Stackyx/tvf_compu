#pragma once
#include "Stocks.hpp"

// This abstract class only handle the final value of the asset price, using the Black-Schole dynamics.


class StocksTerminal : public Stocks
{
public:
	StocksTerminal(ContinuousGenerator* Gen, double s0, double mu, double maturity);
};

