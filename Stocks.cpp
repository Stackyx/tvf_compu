#include "Stocks.hpp"

Stocks::Stocks(double s0, double mu, double maturity)
	: S0(s0), Mu(mu), T(maturity)
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
