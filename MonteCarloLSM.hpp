#ifndef MONTECARLOLSM_HPP
#define MONTECARLOLSM_HPP

#include "MonteCarlo.hpp"

class MonteCarloLSM : public MonteCarlo
{
public:
	MonteCarloLSM(StocksFullPath* stocks, PathDependent* payoff, llong n_sims);

	// std::vector<std::vector<double>> get_Ti(const std::vector<std::vector<std::vector<double>>>& S, const int& i);
	void Solve();
};


#endif