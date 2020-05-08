#include "MonteCarlo.hpp"
#include "NullPayoff.hpp"

MonteCarlo::MonteCarlo(Stocks* stocks, Payoff* payoff, llong n_sims)
	: mc_stocks(stocks), mc_payoff(payoff), N_sims(n_sims), MC_payoff_CV(new NullPayoff()), closedFormValue(0)
{
}

MonteCarlo::MonteCarlo(Stocks* stocks, Payoff* payoff, llong n_sims, Payoff* payoff_CV, double closedFormValue)
	: mc_stocks(stocks), mc_payoff(payoff), N_sims(n_sims), MC_payoff_CV(payoff_CV), closedFormValue(closedFormValue)
{
}

double MonteCarlo::get_price() const
{
	return price;
}

void MonteCarlo::set_N_sims(llong n_sims)
{
	N_sims = n_sims;
}
