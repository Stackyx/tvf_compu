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

		llong n_sims = 10e4;

		std::vector<double> probas = {0.3, 0.1, 0.05, 0.27, 0.19, 0.09};

		PseudoGenerator* firstGen = new LinearCongruential(26645, 12549, 2147483563, 39852);

		UniformGenerator* ecuyer = new EcuyerCombined(1, 1);

		NormalAlgo normal_BM = BoxMuller;
		NormalAlgo normal_CLT = CLT;
		NormalAlgo normal_rej = N_RejectionSamp;

		ContinuousGenerator* norm_BM = new Normal(ecuyer, normal_BM, 0, 1);
		ContinuousGenerator* norm_CLT = new Normal(ecuyer, normal_CLT, 0, 1);
		ContinuousGenerator* norm_rej = new Normal(ecuyer, normal_rej, 0, 1);

		std::vector<double> mu = { 0., 0. };
		std::vector<double> sigma = { 1, 1 };

		ContinuousGenerator* biv_norm = new NormalMultiVariate(ecuyer, mu, sigma, 0.6);

		std::cout << "All ok" << std::endl;

		for (llong i = 0; i < 10; ++i) {
			std::cout << norm_BM->Generate() << std::endl;
		}
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}