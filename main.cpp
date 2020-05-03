#include <iostream>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <exception>
#include <chrono>
#include <vector>
#include <string>

#include "LinearCongruential.hpp"
#include "EcuyerCombined.hpp"
#include "VanDerCorput.hpp"

#include "Normal.hpp"
#include "NormalMultiVariate.hpp"

#include "StandardAntithetic.hpp"

#include "StocksAntitheticTerminal.hpp"
#include "StocksStandardTerminal.hpp"
#include "StocksAntitheticFullPath.hpp"
#include "StocksStandardFullPath.hpp"

#include "Payoff.hpp"
#include "NonPathDependent.hpp"
#include "NPDBasketCall.hpp"
#include "NPDBasketPut.hpp"

#include "MonteCarloEuropean.hpp"

#include "Simulation.hpp"

#include "Tools.hpp"

int main()
{
	try
	{
		UniformGenerator* ecuyer = new EcuyerCombined(1, 1);
		UniformGenerator* ecuyer2 = new EcuyerCombined(1, 1);

		UniformGenerator* vdc = new VanDerCorput(1, 2);
		UniformGenerator* vdc2 = new VanDerCorput(1, 3);

		double mu = 3./ 100.;
		std::vector<double> weights = { 0.5, 0.5 };

		std::vector<std::vector<double>> cov(2, std::vector<double>(2));

		cov[0][0] = 0.3*0.3;
		cov[1][1] = 0.2*0.2;
		cov[0][1] = 0.6*std::sqrt(cov[0][0])*std::sqrt(cov[1][1]);
		cov[1][0] = cov[0][1];

		ContinuousGenerator* biv_norm = new NormalMultiVariate(ecuyer, 0, cov);
		ContinuousGenerator* biv_norm2 = new NormalMultiVariate(ecuyer2, 0, cov);
		ContinuousGenerator* biv_norm3 = new NormalMultiVariate(vdc, vdc2, 0, cov);

		std::cout << "----- MONTECARLO ------" << std::endl;

		llong n_simu = 1000;

		NonPathDependent* call_payoff = new NPDBasketCall(100, weights);
		NonPathDependent* put_payoff = new NPDBasketPut(100, weights);

		R3R1Function* antithetic_function = new StandardAntithetic();

		// --- Standard MC

		StocksTerminal* stocksT = new StocksStandardTerminal(biv_norm, 100, mu, 1);
		MonteCarlo* mc_solver = new MonteCarloEuropean(stocksT, call_payoff, n_simu);

		// --- MC with Antitethic variance reduction

		StocksTerminal* stocksT2 = new StocksAntitheticTerminal(biv_norm2, 100, mu, 1, antithetic_function);
		MonteCarlo* mc_solver_antithetic = new MonteCarloEuropean(stocksT2, call_payoff, llong(n_simu/2));

		// --- MC with quasi random numbers

		StocksTerminal* stocksT3 = new StocksStandardTerminal(biv_norm3, 100, mu, 1);
		MonteCarlo* mc_solver_quasi = new MonteCarloEuropean(stocksT3, call_payoff, n_simu);

		// --- MC with quasi random numbers and antithetic variance reduction

		StocksTerminal* stocksT4 = new StocksAntitheticTerminal(biv_norm3, 100, mu, 1, antithetic_function);
		MonteCarlo* mc_solver_quasi_anti = new MonteCarloEuropean(stocksT4, call_payoff, llong(n_simu/2));

		// ------ MC Simulation ------

		Simulation* MC_simul_standard = new Simulation(mc_solver);
		Simulation* MC_simul_quasi = new Simulation(mc_solver_quasi);
		Simulation* MC_simul_standard_anti = new Simulation(mc_solver_antithetic);
		Simulation* MC_simul_quasi_anti = new Simulation(mc_solver_quasi_anti);

		llong n_sims = 50;

		std::cout << "EXPECTATION AND VARIANCE OF MC" << std::endl;

		MC_simul_standard->compute_expectation(n_sims);
		MC_simul_standard->compute_variance(n_sims);

		MC_simul_quasi->compute_expectation(n_sims);
		MC_simul_quasi->compute_variance(n_sims);

		MC_simul_standard_anti->compute_expectation(n_sims);
		MC_simul_standard_anti->compute_variance(n_sims);

		MC_simul_quasi_anti->compute_expectation(n_sims);
		MC_simul_quasi_anti->compute_variance(n_sims);

		std::cout << "STANDARD :: Expectation = " << MC_simul_standard->get_E() << ", Variance = " << MC_simul_standard->get_V() << std::endl;
		std::cout << "STANDARD ANTITHETIC :: Expectation = " << MC_simul_standard_anti->get_E() << ", Variance = " << MC_simul_standard_anti->get_V() << std::endl;

		std::cout << "QUASI :: Expectation = " << MC_simul_quasi->get_E() << ", Variance = " << MC_simul_quasi->get_V() << std::endl;
		std::cout << "QUASI ANTITHETIC :: Expectation = " << MC_simul_quasi_anti->get_E() << ", Variance = " << MC_simul_quasi_anti->get_V() << std::endl;

		std::cout << "EXPECTATION AND VARIANCE IN FUNCTION OF N_SIMULATION of paths" << std::endl;

		std::vector<double> V(MC_simul_quasi_anti->variance_by_sims(200, { 10, 100, 1000, 10000 }));

		for (llong i = 0; i < V.size(); ++i)
		{
			std::cout << V[i] << ", ";
		}

	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
	
	return 0;
}

void test_functions()
{
	double mu = 3. / 100.;
	std::vector<std::vector<double>> cov(2, std::vector<double>(2));

	cov[0][0] = 0.2 * 0.2;
	cov[1][1] = 0.3 * 0.2;
	cov[0][1] = 0.6 * std::sqrt(cov[0][0]) * std::sqrt(cov[1][1]);
	cov[1][0] = cov[0][1];

	UniformGenerator* ecuyer = new EcuyerCombined(1, 1);
	ContinuousGenerator* biv_norm = new NormalMultiVariate(ecuyer, { mu }, cov);

	std::cout << "----- FULL STOCK PATH -----" << std::endl;

	llong n_steps = 100;
	Stocks* stocksFull = new StocksStandardFullPath(biv_norm, 100, { mu }, 1, n_steps);

	std::vector<std::vector<std::vector<double>>> S_full(stocksFull->Generate(5));

	for (int i = 0; i < S_full.size(); i++)
	{
		for (int j = 0; j < S_full[i].size(); j++)
		{
			std::cout << S_full[i][j][n_steps - 1] << ", ";
		}
		std::cout << std::endl;
	}

	std::cout << "----- Test Basket Payoff ------" << std::endl;

	std::vector<double> weights = { 0.5, 0.5 };
	Payoff* V2 = new NPDBasketCall(100, weights);

	/*std::vector<double> CallBkt = (*V2)(S);

	for (int i = 0; i < S.size(); i++)
	{
		std::cout << CallBkt[i] << ", ";
		std::cout << std::endl;
	}*/
	
	
	
	std::cout<<"----- Test Cholesky --------"<<std::endl;
	std::vector<std::vector<double>> MAtrix;
	MAtrix.resize(4, std::vector<double>(4));
	for(int i = 0; i<4; i++)
	{
		for(int j = 0; j<4; j++)
		{
			MAtrix[i][j] = -1.0;
			if (i==j){
				MAtrix[i][i] = 5.0;
			}	
		}
	}

	std::vector<std::vector<double>> L(MAtrix);
	Cholesky(L);
	std::vector<std::vector<double>> Matrix2(MAtrix);
	inv_sym_defpos(MAtrix, Matrix2);
	
	std::vector<std::vector<double>> multi;
	
	for(int i = 0; i<4; i++)
	{
		std::cout<< Matrix2[i][0] <<", "<<  Matrix2[i][1] <<", "<<  Matrix2[i][2] <<", "<<  Matrix2[i][3] <<std::endl;
	}
	
	mult_matrix(MAtrix, Matrix2, multi);
	for(int i = 0; i<4; i++)
	{
		std::cout<< multi[i][0] <<", "<<  multi[i][1] <<", "<<  multi[i][2] <<", "<<  multi[i][3] <<std::endl;
	}
	
		
		
}
	
