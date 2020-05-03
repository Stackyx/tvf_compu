#pragma once
#include "StocksFullPath.hpp"

class StocksStandardFullPath : public StocksFullPath
{
public:
	StocksStandardFullPath(ContinuousGenerator* gen, double s0, double mu, double maturity, llong n_steps);
	std::vector<std::vector<std::vector<double>>> Generate(llong n_sims);
};

