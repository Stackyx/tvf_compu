#include "MonteCarlo.hpp"

MonteCarlo::MonteCarlo(Stocks* stocks, Payoff* payoff, llong n_sims)
	: mc_stocks(stocks), mc_payoff(payoff), N_sims(n_sims)
{
}

double MonteCarlo::get_price() const
{
	return price;
}
