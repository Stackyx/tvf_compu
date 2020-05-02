#include "Stocks.hpp"
#include <exception>

Stocks::Stocks(double s0, double mu, double maturity)
	: S0(s0), Mu(mu), T(maturity)
{
}

std::vector<std::vector<std::vector<double>>> Stocks::Generate(llong n_sims, R3R1Function* Transform) const
{
	throw std::runtime_error("Not implemented in this class");
}

double Stocks::get_mu() const
{
	return Mu;
}

double Stocks::get_maturity() const
{
	return T;
}
