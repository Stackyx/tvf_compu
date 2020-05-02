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

#include "Tools.hpp"

int main()
{
	try
	{
		UniformGenerator* ecuyer = new EcuyerCombined(1, 1);
		UniformGenerator* ecuyer2 = new EcuyerCombined(1, 1);

		double mu = 0. / 100.;
		std::vector<std::vector<double>> cov(2, std::vector<double>(2));

		cov[0][0] = 0.2*0.2;
		cov[1][1] = 0.2*0.2;
		cov[0][1] = 0.99999999*std::sqrt(cov[0][0])*std::sqrt(cov[1][1]);
		cov[1][0] = cov[0][1];

		ContinuousGenerator* biv_norm = new NormalMultiVariate(ecuyer, { mu }, cov);
		ContinuousGenerator* biv_norm2 = new NormalMultiVariate(ecuyer2, { mu }, cov);

		std::vector<double> weights = { 0.5, 0.5 };

		std::cout << "----- MONTECARLO ------" << std::endl;

		llong n_simu = 1000;

		NonPathDependent* call_payoff = new NPDBasketCall(100, weights);
		NonPathDependent* put_payoff = new NPDBasketPut(100, weights);

		auto start = std::chrono::high_resolution_clock::now();

		StocksTerminal* stocksT = new StocksStandardTerminal(biv_norm, 100, { mu }, 1);
		MonteCarlo* mc_solver = new MonteCarloEuropean(stocksT, call_payoff, n_simu);

		mc_solver->Solve();
		
		auto stop = std::chrono::high_resolution_clock::now();

		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		std::cout << "Time taken = " << duration.count() << "ms" << std::endl;

		start = std::chrono::high_resolution_clock::now();

		R3R1Function* antithetic_function = new StandardAntithetic();
		StocksTerminal* stocksT2 = new StocksAntitheticTerminal(biv_norm2, 100, { mu }, 1, antithetic_function);
		MonteCarlo* mc_solver_antithetic = new MonteCarloEuropean(stocksT2, call_payoff, n_simu);

		mc_solver_antithetic->Solve();

		stop = std::chrono::high_resolution_clock::now();

		duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		std::cout << "Time taken = " << duration.count() << "ms" << std::endl;

		NormalAlgo type = BoxMuller;

		UniformGenerator* vdc = new VanDerCorput(1, 13);
		ContinuousGenerator* norm = new Normal(vdc, type, 0, 1);
		norm->export_csv(100000, "norm3.csv");

		//ecuyer->export_csv(1000, "ecuyer.csv");
		ContinuousGenerator* biv_norm3 = new NormalMultiVariate(vdc, { mu }, cov);
		start = std::chrono::high_resolution_clock::now();

		StocksTerminal* stocksT3 = new StocksStandardTerminal(biv_norm3, 100, { mu }, 1);
		MonteCarlo* mc_solver_quasi = new MonteCarloEuropean(stocksT3, call_payoff, n_simu);

		mc_solver_quasi->Solve();

		stop = std::chrono::high_resolution_clock::now();

		duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

		std::cout << "Time taken = " << duration.count() << "ms" << std::endl;

		std::cout << "Price = " << mc_solver->get_price() << std::endl;
		std::cout << "Price MC Antithetic = " << mc_solver_antithetic->get_price() << std::endl;
		std::cout << "Price MC Quasi = " << mc_solver_quasi->get_price() << std::endl;
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

	std::vector<double> CallBkt = (*V2)(S);

	for (int i = 0; i < S.size(); i++)
	{
		std::cout << CallBkt[i] << ", ";
		std::cout << std::endl;
	}
	
	
	
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
	
