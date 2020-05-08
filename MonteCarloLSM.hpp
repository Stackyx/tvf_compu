#ifndef MONTECARLOLSM_HPP
#define MONTECARLOLSM_HPP

#include "MonteCarlo.hpp"
#include "Basis.hpp"
#include "Tools.hpp"

class MonteCarloLSM : public MonteCarlo
{
public:
	MonteCarloLSM(StocksFullPath* stocks, PathDependent* payoff, llong n_sims, Basis* BasisFunction);
	MonteCarloLSM(StocksFullPath* stocks, PathDependent* payoff, llong n_sims, Basis* BasisFunction, PathDependent* payoff_CV, double closedFormValue);
	
	void Solve();
	
private:
	Basis* LSM_Basis;
	PathDependent* LSM_payoff;
};

#endif