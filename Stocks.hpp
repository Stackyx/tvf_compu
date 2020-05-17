#pragma once
#include <vector>
#include "R3R1Function.hpp"
#include <stdexcept> 
#include "ContinuousGenerator.hpp"

// This abstract call handles the generation of n correlated assets value at time T.
// This can also generate a full path value.

// The number of assets is ruled by the covariance matrix size of the ContinuousGenerator.

typedef unsigned long long llong;

class Stocks
{
public:
	Stocks(ContinuousGenerator* Gen, double s0, double mu, double maturity);

	virtual std::vector<std::vector<std::vector<double>>> Generate(llong n_sims) = 0;

	double get_mu() const;
	double get_maturity() const;

protected:
	ContinuousGenerator* Gen;

	double Mu, S0, T;

	std::vector<std::vector<double>> W;
	std::vector<std::vector<std::vector<double>>> S;
};

