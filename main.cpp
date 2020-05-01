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

#include "Stocks.hpp"
#include "StocksTerminal.hpp"
#include "StocksFullPath.hpp"

#include "Vanilla.hpp"
#include "VanillaCall.hpp"
#include "VanillaPut.hpp"
#include "BasketPayoff.hpp"
#include "BasketPut.hpp"
#include "BasketCall.hpp"

int main()
{
	try
	{
		UniformGenerator* ecuyer = new EcuyerCombined(1, 1);

		std::vector<double> mu = { 3./100., 6./100. };
		std::vector<std::vector<double>> cov(2, std::vector<double>(2));

		cov[0][0] = 0.2*0.2;
		cov[1][1] = 0.3*0.3;
		cov[0][1] = -0.6*std::sqrt(cov[0][0])*std::sqrt(cov[1][1]);
		cov[1][0] = cov[0][1];

		ContinuousGenerator* biv_norm = new NormalMultiVariate(ecuyer, mu, cov);

		Stocks* stocks = new StocksTerminal(biv_norm, { 100, 125 }, mu, 1);
		std::vector<std::vector<std::vector<double>>> S(stocks->Generate(5));

		for (int i = 0; i < S.size(); i++)
		{
			for (int j = 0; j < S[i].size(); j++)
			{
				std::cout << S[i][j][0] << ", ";
			}
			std::cout << std::endl;
		}
		
		std::cout << "----- FULL STOCK PATH -----" << std::endl;

		llong n_steps = 100;
		Stocks* stocksFull = new StocksFullPath(biv_norm, { 100, 125 }, mu, 1, n_steps);

		std::vector<std::vector<std::vector<double>>> S_full(stocksFull->Generate(5));

		for (int i = 0; i < S_full.size(); i++)
		{
			for (int j = 0; j < S_full[i].size(); j++)
			{
				std::cout << S_full[i][j][n_steps-1] << ", ";
			}
			std::cout << std::endl;
		}

		std::cout<<"----- Test Payoff ------" << std::endl;
		Vanilla* V1 = new VanillaCall(100);
		std::cout << (*V1)(110.5) <<", "<< (*V1)(90.5)<<std::endl;
		Vanilla* V2 = new VanillaPut(100);
		std::cout << (*V2)(110.5) <<", "<< (*V2)(90.5)<<std::endl;
		
		std::vector<double> weights = {0.5, -0.5, 0.9, 0.1};
		std::vector<double> spot1 = {100, 100, 110, 120.1};
		std::vector<double> spot2 = {100, 100, 90, 80.1};
		BasketPayoff* V3 = new BasketCall(100, weights);
		std::cout << (*V3)(spot1) <<", "<< (*V3)(spot2)<<std::endl;
		BasketPayoff* V4 = new BasketPut(100, weights);
		std::cout << (*V4)(spot1) <<", "<< (*V4)(spot2)<<std::endl;

	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
	
	return 0;
}