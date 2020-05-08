#pragma once
#include "MonteCarlo.hpp"

class Simulation
{
public:
	Simulation(MonteCarlo* mc_model);

	void compute_expectation(llong n_sims);
	void compute_variance(llong n_sims);

	std::vector<double> expectation_by_sims(llong exp_simul, std::vector<double> mc_simul);
	std::vector<double> variance_by_sims(llong var_simul, std::vector<double> mc_simul);

	void expectation_by_sims(llong exp_simul, std::vector<double> mc_simul, std::string fname);
	void variance_by_sims(llong var_simul, std::vector<double> mc_simul, std::string fname);
//for Control variate
	void compute_expectation(llong n_sims, Payoff* MC_payoff_CV, double ClosedFormValue);
	void compute_variance(llong n_sims, Payoff* MC_payoff_CV, double ClosedFormValue);

	std::vector<double> expectation_by_sims(llong exp_simul, std::vector<double> mc_simul, Payoff* MC_payoff_CV, double ClosedFormValue);
	std::vector<double> variance_by_sims(llong var_simul, std::vector<double> mc_simul, Payoff* MC_payoff_CV, double ClosedFormValue);

	void expectation_by_sims(llong exp_simul, std::vector<double> mc_simul, std::string fname, Payoff* MC_payoff_CV, double ClosedFormValue);
	void variance_by_sims(llong var_simul, std::vector<double> mc_simul, std::string fname, Payoff* MC_payoff_CV, double ClosedFormValue);
	
	double get_E();
	double get_V();

private:
	MonteCarlo* MC_model;
	
	double Sim_CFV;
	
	double E, V;
	bool isExpectationComputed = false;
	bool isVarianceComputed = false;
};

