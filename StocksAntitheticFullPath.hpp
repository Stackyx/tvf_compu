#pragma once
#include "StocksFullPath.hpp"

class StocksAntitheticFullPath : public StocksFullPath
{
	StocksAntitheticFullPath(ContinuousGenerator* gen, double s0, double mu, double maturity, llong n_steps, R3R1Function* Transform);

	std::vector<std::vector<std::vector<double>>> Generate(llong n_sims);
private:
	R3R1Function* Transform;
	std::vector<std::vector<double>> W_transform;
};

