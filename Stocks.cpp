#include "Stocks.hpp"
#include <exception>

Stocks::Stocks(ContinuousGenerator* Gen, double s0, double mu, double maturity)
	: Gen(Gen), S0(s0), Mu(mu), T(maturity)
{
}

double Stocks::get_mu() const
{
	return Mu;
}

double Stocks::get_maturity() const
{
	return T;
}
