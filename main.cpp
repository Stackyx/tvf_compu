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
#include "PathDependent.hpp"
#include "PDBasketCall.hpp"

#include "MonteCarloEuropean.hpp"
#include "MonteCarloLSM.hpp"

#include "BasisLaguerre.hpp"
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
		PathDependent* call_payoff_PD = new PDBasketCall(100, weights);

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

		UniformGenerator* vdc = new VanDerCorput(1, 2);
		ContinuousGenerator* norm = new Normal(vdc, type, 0, 1);
		//vdc->export_csv(10000, "VDC2.csv");

		ContinuousGenerator* biv_norm3 = new NormalMultiVariate(vdc, { mu }, cov);
		start = std::chrono::high_resolution_clock::now();

		StocksTerminal* stocksT3 = new StocksStandardTerminal(biv_norm3, 100, { mu }, 1);
		MonteCarlo* mc_solver_quasi = new MonteCarloEuropean(stocksT3, call_payoff, n_simu);

		mc_solver_quasi->Solve();

		stop = std::chrono::high_resolution_clock::now();

		duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

		std::cout << "Time taken = " << duration.count() << "ms" << std::endl;

		start = std::chrono::high_resolution_clock::now();
		
		Basis* BLG = new BasisLaguerre(3);
		StocksStandardFullPath* stocksFP = new StocksStandardFullPath(biv_norm, 100, { mu }, 1, 100);
		MonteCarloLSM* mc_solverLSM = new MonteCarloLSM(stocksFP, call_payoff_PD, n_simu, BLG);

		mc_solverLSM->Solve();
		
		stop = std::chrono::high_resolution_clock::now();

		duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		std::cout << "Time taken = " << duration.count() << "ms" << std::endl;
		
		std::cout << "Price = " << mc_solver->get_price() << std::endl;
		std::cout << "Price MC Antithetic = " << mc_solver_antithetic->get_price() << std::endl;
		std::cout << "Price MC Quasi = " << mc_solver_quasi->get_price() << std::endl;
		std::cout << "Price LSM = " << mc_solverLSM->get_price() << std::endl;
		

		// std::cout<<"----- Test Cholesky --------"<<std::endl;
		// std::vector<std::vector<double>> Matrix(mc_solverLSM->A);
		// std::vector<std::vector<double>> Matrix2(mc_solverLSM->Ainv);
		// std::vector<std::vector<double>> L(BLG->get_matrix_L(mc_solverLSM->X));

		
		// for(int i = 0; i<L.size(); i++)
		// {
			// for (int j=0; j<L[0].size();j++)
			// {
				// std::cout<< L[i][j] <<", ";
			// }
			// std::cout<<std::endl;
		// }
		// std::cout<<(mc_solverLSM->X)[0]<<std::endl;

		// inv_sym_defpos(Matrix, Matrix2);
		// inv_sym_defpos(Matrix, Matrix2);
		// std::vector<std::vector<double>> Multi;
		// mult_matrix(Matrix, Matrix2, Multi);
		
		// for(int i = 0; i<Matrix.size(); i++)
		// {
			// for (int j=0; j<Matrix[0].size();j++)
			// {
				// std::cout<< Matrix[i][j] <<", ";
			// }
			// std::cout<<std::endl;
		// }
		
		// for(int i = 0; i<Matrix2.size(); i++)
		// {
			// for (int j=0; j<Matrix2[0].size();j++)
			// {
				// std::cout<< Matrix2[i][j] <<", ";
			// }
			// std::cout<<std::endl;
		// }


		// std::vector<std::vector<double>> MAtrix;
		// MAtrix.resize(4, std::vector<double>(4));
		// for(int i = 0; i<4; i++)
		// {
			// for(int j = 0; j<4; j++)
			// {
				// MAtrix[i][j] = -1.0;
				// if (i==j){
					// MAtrix[i][i] = 5.0;
				// }	
			// }
		// }

		// std::vector<std::vector<double>> L(MAtrix);
		// Cholesky(L);
		// std::vector<std::vector<double>> Matrix22(MAtrix);
		// inv_sym_defpos(MAtrix, Matrix22);
		
		// std::vector<std::vector<double>> multi;
		
		// for(int i = 0; i<4; i++)
		// {
			// std::cout<< Matrix22[i][0] <<", "<<  Matrix22[i][1] <<", "<<  Matrix22[i][2] <<", "<<  Matrix22[i][3] <<std::endl;
		// }
		
		// mult_matrix(MAtrix, Matrix22, multi);
		// for(int i = 0; i<4; i++)
		// {
			// std::cout<< multi[i][0] <<", "<<  multi[i][1] <<", "<<  multi[i][2] <<", "<<  multi[i][3] <<std::endl;
		// }
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

	// std::vector<double> CallBkt = (*V2)(S);

	// for (int i = 0; i < S.size(); i++)
	// {
		// std::cout << CallBkt[i] << ", ";
		// std::cout << std::endl;
	// }
	
	
	
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
	
