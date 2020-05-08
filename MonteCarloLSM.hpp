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
	void Solve(PathDependent* MC_payoff_CV, double ClosedFormValue);
	void Solve(Payoff* MC_payoff_CV, double ClosedFormValue);

	// std::vector<std::vector<double>> A;
	// std::vector<std::vector<double>> Ainv;
	// std::vector<double> X;
private:
	Basis* LSM_Basis;
	PathDependent* LSM_payoff;
};


void display_mat(const std::vector<std::vector<double>>& A);
void display_vect(const std::vector<double>& A);

#endif