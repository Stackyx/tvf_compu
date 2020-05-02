#pragma once
#include <vector>
#include "R3R1Function.hpp"
#include <stdexcept> 

typedef unsigned long long llong;

class Stocks
{
public:
	Stocks(double s0, double mu, double maturity);
	virtual std::vector<std::vector<std::vector<double>>> Generate(llong n_sims) const = 0;
	virtual std::vector<std::vector<std::vector<double>>> Generate(llong n_sims, R3R1Function* Transform) const;
	double get_mu() const;
	double get_maturity() const;
protected:
	double Mu, S0, T;
};

