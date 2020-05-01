#include "ContinousGenerator.hpp"
#include "discrete_generator.hpp"
#include "EcuyerCombined.hpp"
#include "LinearCongruential.hpp"
#include "Normal.hpp"
#include "NormalMultiVariate.hpp"
#include "pseudo_generator.hpp"
#include "random_generator.hpp"

#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{	

//Generate Linear
	// LinearCongruential Gen(27, 17, 43, 100);
	
	// for (size_t i = 0; i <= 3;  ++i)
	// {
		// std::cout << "R" << i << " = " << Gen.Generate() << std::endl;
	// }
	 
//Generate Lecuyer	 
	// Lecuyer Gen(1, 1);
	// // Lecuyer* ptr = new Lecuyer(1,1);
	// for (size_t i = 0; i <= 3;  ++i)
	// {
		// std::cout << "R" << i << " = " << Gen.Generate() << std::endl;
		// // std::cout << "R" << i << " = " << ptr->Generate() << std::endl;
	// }
	// std::cout<< Gen.Mean(1000000) << std::endl;
	// std::cout<< Gen.Variance(1000000) << std::endl;
	// std::cout<< 1/12. << std::endl;
	
//Head and Tail test
	// UniformGenerator* ptr = new Lecuyer(1,1);
	// HeadTail Head(ptr);
	
	// for (size_t i = 0; i <= 3;  ++i)
	// {
		// std::cout << "R" << i << " = " << Head.Generate() << std::endl;
		std::cout << "R" << i << " = " << ptr->Generate() << std::endl;
	// }
	// std::cout<< Head.Mean(10000000) << std::endl;
	// std::cout<< Head.Variance(10000000) << std::endl;
	
//Bernouilli test	
	// UniformGenerator* ptr = new Lecuyer(1,1);
	// Bernouilli Bern(0.2, ptr);
	
	// for (size_t i = 0; i <= 3;  ++i)
	// {
		// std::cout << "R" << i << " = " << Bern.Generate() << std::endl;
		// // std::cout << "R" << i << " = " << ptr->Generate() << std::endl;
	// }
	// std::cout<< Bern.Mean(10000000) << std::endl;
	// std::cout<< Bern.Variance(10000000) << std::endl;

//Binomial test	
	// UniformGenerator* ptr = new Lecuyer(1,1);
	// Binomial Bern(100, 0.2, ptr);
	
	// for (size_t i = 0; i <= 3;  ++i)
	// {
		// std::cout << "R" << i << " = " << Bern.Generate() << std::endl;
		// // std::cout << "R" << i << " = " << ptr->Generate() << std::endl;
	// }
	// std::cout<< Bern.Mean(10000000) << std::endl;
	// std::cout<< Bern.Variance(10000000) << std::endl;
	
	
	
//FiniteSet test	
	// UniformGenerator* ptr = new Lecuyer(1,1);
	// std::vector<double> prob = {0.1, 0, 0, 0.9};
	// FiniteSet FS(ptr, prob);
	
	// for (size_t i = 0; i <= 10;  ++i)
	// {
		// std::cout << "R" << i << " = " << FS.Generate() << std::endl;
		// // std::cout << "R" << i << " = " << ptr->Generate() << std::endl;
	// }
	// std::cout<< FS.Mean(1000000) << std::endl;
	// std::cout<< FS.Variance(1000000) << std::endl;
	
//Poisson test	
	// UniformGenerator* ptr = new Lecuyer(1,1);
	// PoissonFirstAlgo p(2, ptr);
	
	// for (size_t i = 0; i <= 6;  ++i)
	// {
		// std::cout << "R" << i << " = " << p.Generate() << std::endl;
		// // std::cout << "facto" << i << " = " << p.facto(i) << std::endl;
	// }
	// std::cout<< p.Mean(1000000) << std::endl;	
	// std::cout<< p.Variance(1000000) << std::endl;
	
//expo test	
	// UniformGenerator* ptr = new Lecuyer(1,1);
	// Exponential_Inverse ee(2, ptr);
	
	// for (size_t i = 0; i <= 6;  ++i)
	// {
		// std::cout << "R" << i << " = " << ee.Generate() << std::endl;
		// // std::cout << "facto" << i << " = " << p.facto(i) << std::endl;
	// }
	// std::cout<< ee.Mean(1000000) << std::endl;	
	// std::cout<< ee.Variance(1000000) << std::endl;
	
//Normal BM test	
	// UniformGenerator* ptr = new Lecuyer(1,1);
	// Normal_BM BM(ptr, 0,1);
	
	// for (size_t i = 0; i <= 6;  ++i)
	// {
		// std::cout << "R" << i << " = " << BM.Generate() << std::endl;
	// }
	// std::cout<< BM.Mean(10000000) << std::endl;	
	// std::cout<< BM.Variance(1000000) << std::endl;

//Normal CTL test	
	// UniformGenerator* ptr = new Lecuyer(1,1);
	// Normal_CTL CTL(ptr, 0,2, 12);
	
	// for (size_t i = 0; i <= 6;  ++i)
	// {
		// std::cout << "R" << i << " = " << CTL.Generate() << std::endl;
	// }
	// std::cout<< CTL.Mean(10000) << std::endl;	
	// std::cout<< CTL.Variance(10000) << std::endl;
	
	return 0;

}
