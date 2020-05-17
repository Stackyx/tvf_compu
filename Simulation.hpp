#pragma once
#include "MonteCarlo.hpp"

// This class handles the simulation of a MonteCarlo class.
// You can compute its expectation, variance, write to a file expectations/variance in function of iterations, etc.

class Simulation
{
public:
	Simulation(MonteCarlo* mc_model);

	void compute_expectation(llong n_sims);
	void compute_variance(llong n_sims);

	std::vector<double> expectation_by_sims(llong exp_simul, const std::vector<llong>& mc_simul);
	std::vector<double> variance_by_sims(llong var_simul, const std::vector<llong>& mc_simul);

	void expectation_by_sims(llong exp_simul, const std::vector<llong>& mc_simul, std::string fname);
	void variance_by_sims(llong var_simul, const std::vector<llong>& mc_simul, std::string fname);

	double get_E();
	double get_V();

private:
	MonteCarlo* MC_model;
	
	double Sim_CFV;
	
	double E, V;
	bool isExpectationComputed = false;
	bool isVarianceComputed = false;
};

