#pragma once
#include "StocksFullPath.hpp"

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

