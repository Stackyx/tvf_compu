#pragma once
#include "StocksFullPath.hpp"
#include "StocksTerminal.hpp"
#include "PathDependent.hpp"
#include "NonPathDependent.hpp"
#include <algorithm>
#include <numeric>

class MonteCarlo
{
public:

	MonteCarlo(Stocks* stocks, Payoff* payoff, llong n_sims);
	MonteCarlo(Stocks* stocks, Payoff* payoff, llong n_sims, Payoff* payoff_CV, double closedFormValue);

	virtual void Solve() = 0;
	
	double get_price() const;

	void set_N_sims(llong n_sims);
protected:

	double price, closedFormValue;
	llong N_sims;

	Stocks* mc_stocks;
	Payoff* mc_payoff, *MC_payoff_CV;
};

