#ifndef MONTECARLOLSM_HPP
#define MONTECARLOLSM_HPP

#include "MonteCarlo.hpp"
#include "Basis.hpp"
#include "Tools.hpp"

class MonteCarloLSM : public MonteCarlo
{
public:
	MonteCarloLSM(StocksFullPath* stocks, PathDependent* payoff, llong n_sims, Basis* BasisFunction);
	
	void Solve();
	// std::vector<std::vector<double>> A;
	// std::vector<std::vector<double>> Ainv;
	// std::vector<double> X;
private:
	Basis* LSM_Basis;
	PathDependent* LSM_payoff;
};


#endif