#pragma once
#include "Stocks.hpp"
#include "ContinuousGenerator.hpp"

// Another abstract class to generate a full path.
// The second constructor can handle dividends payment during the life of the asset.

class StocksFullPath : public Stocks
{
public:
	StocksFullPath(ContinuousGenerator* gen, double s0, double mu, double maturity, llong n_steps);
	StocksFullPath(ContinuousGenerator* gen, double s0, double mu, double maturity, const std::vector<double>& divividends, const std::vector<double>& date_dividends, llong n_steps);
protected:
	llong N_steps;
protected:
	std::vector<double> Div = { 0. };
	std::vector<double> Date_Div = { 0. };
};

