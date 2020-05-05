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

	virtual void Solve() = 0;
	virtual void Solve(Payoff* MC_payoff_CV, double ClosedFormValue)=0;
	
	double get_price() const;

	void set_N_sims(llong n_sims);
protected:

	double price;
	llong N_sims;

	Stocks* mc_stocks;
	Payoff* mc_payoff;

};

