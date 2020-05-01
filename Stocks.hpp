#pragma once
#include <vector>

typedef unsigned long long llong;

class Stocks
{
public:
	Stocks(double s0, double mu, double maturity);
	virtual std::vector<std::vector<std::vector<double>>> Generate(llong n_sims) = 0;
	double get_mu();
	double get_maturity();
protected:
	double Mu, S0, T;
};

