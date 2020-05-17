#pragma once
#include "StocksFullPath.hpp"

// Instantiable class that generate a full asset stock path price implementing the Antithetic variance reduction method.

// INPUTS : Continuous random number generator, double S0, double risk free rate, double maturity and llong number of steps
// This class can also handle dividends payment. Input the ABSOLUTE values of the dividend payment and their dates between 0 and maturity.


class StocksAntitheticFullPath : public StocksFullPath
{
public:
	StocksAntitheticFullPath(ContinuousGenerator* gen, double s0, double mu, double maturity, llong n_steps, R3R1Function* Transform);
	StocksAntitheticFullPath(ContinuousGenerator* gen, double s0, double mu, double maturity, R3R1Function* Transform, const std::vector<double>& dividends, const std::vector<double>& date_dividends, llong n_steps);


	std::vector<std::vector<std::vector<double>>> Generate(llong n_sims);
private:
	R3R1Function* Transform;
	std::vector<std::vector<double>> W_transform;
};

