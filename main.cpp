#include <iostream>
#include <fstream>
#include <exception>
#include <chrono>

#include "LinearCongruential.hpp"
#include "EcuyerCombined.hpp"

#include "Normal.hpp"
#include "NormalMultiVariate.hpp"

int main()
{
	try
	{
		PseudoGenerator* firstGen = new LinearCongruential(26645, 12549, 2147483563, 39852);

		UniformGenerator* ecuyer = new EcuyerCombined(1, 1);

		std::vector<double> mu = { 0., 0. };
		std::vector<std::vector<double>> cov(2, std::vector<double>(2));

		cov[0][0] = 1;
		cov[1][1] = 1;
		cov[0][1] = 0.6;
		cov[1][0] = 0.6;

		ContinuousGenerator* biv_norm = new NormalMultiVariate(ecuyer, mu, cov);
		std::vector<std::vector<double>> W(biv_norm->Generate(100));

		for (int i = 0; i < W.size(); ++i)
		{
			for (int j = 0; j < W[i].size(); ++j)
			{
				std::cout << W[i][j] << ", ";
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