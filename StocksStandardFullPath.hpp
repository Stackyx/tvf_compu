#pragma once
#include "StocksFullPath.hpp"

// Instantiable class that generate a full asset stock path price.

// INPUTS : Continuous random number generator, double S0, double risk free rate, double maturity and llong number of steps
// This class can also handle dividends payment. Input the ABSOLUTE values of the dividend payment and their dates between 0 and maturity.

class StocksStandardFullPath : public StocksFullPath
{
public:
	StocksStandardFullPath(ContinuousGenerator* gen, double s0, double mu, double maturity, llong n_steps);
	StocksStandardFullPath(ContinuousGenerator* gen, double s0, double mu, double maturity, const std::vector<double>& dividends, const std::vector<double>& date_dividends, llong n_steps);

	std::vector<std::vector<std::vector<double>>> Generate(llong n_sims);
};

