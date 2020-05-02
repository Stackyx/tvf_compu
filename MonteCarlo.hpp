#pragma once
#include "StocksFullPath.hpp"
#include "StocksTerminal.hpp"
#include "PathDependent.hpp"
#include "NonPathDependent.hpp"

class MonteCarlo
{
public:

	MonteCarlo(Stocks* stocks, Payoff* payoff, llong n_sims);

	virtual void Solve() = 0;
	double get_price() const;

protected:

	double price;
	llong N_sims;

	Stocks* mc_stocks;
	Payoff* mc_payoff;

};

