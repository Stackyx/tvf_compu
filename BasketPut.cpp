#include "BasketPut.hpp"
#include <algorithm>
#include <numeric>

BasketPut::BasketPut(double strike, std::vector<double> weights)
	:BasketPayoff(strike, weights)
{

}

double BasketPut::operator()(double x)
{
	if (len_weights != 1)
	{
		std::cout<<"WARNING: Please enter "<< len_weights << " Spot prices" << std::endl;
		std::cout<<"Result output is wrong!!!"<< std::endl;
	}
	return (x < E_strike)? E_strike - x : 0;
}

double BasketPut::operator()(std::vector<double> x)
{
	if (len_weights > x.size())
	{
		std::cout<<"WARNING: Please enter "<< len_weights << " Spot prices" << std::endl;
		std::cout<<"There are "<< len_weights - x.size() <<" Spot missing" <<std::endl;
		std::cout<<"Result output is wrong!!!"<< std::endl;
		return (x[0] < E_strike)? E_strike - x[0]: 0;
	}
	if (len_weights < x.size())
	{
		std::cout<<"WARNING: Please enter "<< len_weights << " Spot prices" << std::endl;
		std::cout<<"There are "<< x.size()- len_weights <<" more spot than weights" <<std::endl;
		std::cout<<"Result output is wrong!!!"<< std::endl;
		return (x[0] < E_strike)? E_strike - x[0] : 0;
	}
	if (len_weights == x.size())
	{
		std::vector<double> m(len_weights);
		std::transform( E_weights.begin(), E_weights.end(), x.begin(), m.begin(), std::multiplies<double>());
		double sum = std::accumulate(m.begin(),m.end(),0.0);
		return (sum < E_strike)? E_strike -sum : 0;
	}
}