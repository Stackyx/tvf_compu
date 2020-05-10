#include "Simulation.hpp"
#include <fstream>

Simulation::Simulation(MonteCarlo* mc_model)
	: MC_model(mc_model)
{
}


void Simulation::compute_expectation(llong n_sims)
{
	E = 0;

	for (llong i = 0; i < n_sims; ++i)
	{
		MC_model->Solve();
		E += MC_model->get_price()/n_sims;
	}

	isExpectationComputed = true;
}

void Simulation::compute_variance(llong n_sims)
{
	V = 0;
	double price;

	if (!isExpectationComputed)
	{
		compute_expectation(n_sims);
	}

	for (llong i = 0; i < n_sims; ++i)
	{
		MC_model->Solve();
		price = MC_model->get_price();

		V += (price - E) * (price - E) / n_sims;
	}

	isVarianceComputed = true;
}


std::vector<double> Simulation::expectation_by_sims(llong exp_simul, const std::vector<llong>& mc_simul)
{
	std::vector<double> E_arr(mc_simul.size());

	for (llong i = 0; i < mc_simul.size(); ++i)
	{
		MC_model->set_N_sims(mc_simul[i]);
		compute_expectation(exp_simul);
		E_arr[i] = E;
	}

	return E_arr;
}


std::vector<double> Simulation::variance_by_sims(llong var_simul, const std::vector<llong>& mc_simul)
{
	std::vector<double> V_arr(mc_simul.size());

	for (llong i = 0; i < mc_simul.size(); ++i)
	{
		isExpectationComputed = false;
		MC_model->set_N_sims(mc_simul[i]);
		compute_variance(var_simul);
		V_arr[i] = V;
	}

	return V_arr;
}

void Simulation::expectation_by_sims(llong exp_simul, const std::vector<llong>& mc_simul, std::string fname)
{
	std::ofstream f;
	f.open(fname);

	for (llong i = 0; i < mc_simul.size(); ++i)
	{
		MC_model->set_N_sims(mc_simul[i]);
		compute_expectation(exp_simul);
		f << mc_simul[i] << "," << E << "\n";
	}

	f.close();
}


void Simulation::variance_by_sims(llong var_simul, const std::vector<llong>& mc_simul, std::string fname)
{
	std::ofstream f;
	f.open(fname);

	for (llong i = 0; i < mc_simul.size(); ++i)
	{
		isExpectationComputed = false;
		MC_model->set_N_sims(mc_simul[i]);
		compute_variance(var_simul);
		f << mc_simul[i] << "," << V << "\n";
	}

	f.close();

}

double Simulation::get_E()
{
	if (!isExpectationComputed)
	{
		throw std::runtime_error("The expectation is not computed.");
	}

	return E;
}

double Simulation::get_V()
{
	if (!isVarianceComputed)
	{
		throw std::runtime_error("The variance is not computed.");
	}

	return V;
}
