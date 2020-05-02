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

#include "Normal.hpp"
#include "NormalMultiVariate.hpp"

#include "StandardAntithetic.hpp"

#include "StocksAntitheticTerminal.hpp"
#include "StocksStandardTerminal.hpp"
#include "StocksFullPath.hpp"

#include "Payoff.hpp"
#include "NonPathDependent.hpp"
#include "NPDBasketCall.hpp"
#include "NPDBasketPut.hpp"

#include "MonteCarloEuropean.hpp"

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
		cov[0][1] = 0.99999*std::sqrt(cov[0][0])*std::sqrt(cov[1][1]);
		cov[1][0] = cov[0][1];

		ContinuousGenerator* biv_norm = new NormalMultiVariate(ecuyer, { mu }, cov);
		ContinuousGenerator* biv_norm2 = new NormalMultiVariate(ecuyer2, { mu }, cov);

		std::vector<double> weights = { 0.5, 0.5 };

		std::cout << "----- MONTECARLO ------" << std::endl;

		R3R1Function* antithetic_function = new StandardAntithetic();

		NonPathDependent* call_payoff = new NPDBasketCall(100, weights);
		NonPathDependent* put_payoff = new NPDBasketPut(100, weights);

		StocksTerminal* stocksT = new StocksStandardTerminal(biv_norm, 100, { mu }, 1);
		StocksTerminal* stocksT2 = new StocksAntitheticTerminal(biv_norm2, 100, { mu }, 1, antithetic_function);

		MonteCarlo* mc_solver = new MonteCarloEuropean(stocksT, call_payoff, 10000);
		MonteCarlo* mc_solver_antithetic = new MonteCarloEuropean(stocksT2, call_payoff, 10000);

		mc_solver->Solve();
		mc_solver_antithetic->Solve();

		std::cout << "Price = " << mc_solver->get_price() << std::endl;
		std::cout << "Price MC Antithetic = " << mc_solver_antithetic->get_price() << std::endl;
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
	Stocks* stocksFull = new StocksFullPath(biv_norm, 100, { mu }, 1, n_steps);

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

	//std::vector<double> weights = { 0.5, 0.5 };
	//payoff* v2 = new npdbasketcall(100, weights);

	//std::vector<double> callbkt = (*v2)(s);

	//for (int i = 0; i < s.size(); i++)
	//{
	//	std::cout << callbkt[i] << ", ";
	//	std::cout << std::endl;
	//}
}
	