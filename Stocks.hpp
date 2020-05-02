#pragma once
#include <vector>
#include "R3R1Function.hpp"
#include <stdexcept> 
#include "ContinuousGenerator.hpp"

typedef unsigned long long llong;

class Stocks
{
public:
	Stocks(ContinuousGenerator* Gen, double s0, double mu, double maturity);

	virtual std::vector<std::vector<std::vector<double>>> Generate(llong n_sims) const = 0;

	double get_mu() const;
	double get_maturity() const;
protected:
	double Mu, S0, T;
	ContinuousGenerator* Gen;
};

