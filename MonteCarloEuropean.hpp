#pragma once
#include "MonteCarlo.hpp"
#include "StocksFullPath.hpp"
#include "StocksTerminal.hpp"
#include "PathDependent.hpp"
#include "NonPathDependent.hpp"

class MonteCarloEuropean : public MonteCarlo
{
public:
	MonteCarloEuropean(StocksTerminal* stocks, Payoff* payoff);
	void Solve();
private:
};

