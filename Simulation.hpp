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

	double get_E();
	double get_V();

private:
	MonteCarlo* MC_model;

	double E, V;
	bool isExpectationComputed = false;
	bool isVarianceComputed = false;
};

