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

int main()
{
	try
	{
		UniformGenerator* ecuyer = new EcuyerCombined(1, 1);

		std::vector<double> mu = { 3./100., 6./100. };
		std::vector<std::vector<double>> cov(2, std::vector<double>(2));

		cov[0][0] = 0.2*0.2;
		cov[1][1] = 0.3*0.3;
		cov[0][1] = 0.6*std::sqrt(cov[0][0])*std::sqrt(cov[1][1]);
		cov[1][0] = cov[0][1];

		ContinuousGenerator* biv_norm = new NormalMultiVariate(ecuyer, mu, cov);

		Stocks* stocks = new StocksTerminal(biv_norm, 100, mu, .5);
		std::vector<std::vector<std::vector<double>>> S(stocks->Generate(100));

		for (int i = 0; i < S.size(); i++)
		{
			for (int j = 0; j < S[i].size(); j++)
			{
				std::cout << S[i][j][0] << ", ";
			}
			std::cout << std::endl;
		}

	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
	

	return 0;
}