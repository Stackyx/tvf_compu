#pragma once
#include "Stocks.hpp"
#include "ContinuousGenerator.hpp"

class StocksFullPath : public Stocks
{
public:
	StocksFullPath(ContinuousGenerator* gen, double s0, double mu, double maturity, llong n_steps);
protected:
	llong N_steps;
};

