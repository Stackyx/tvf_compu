#include "NPDBasketPut.hpp"
#include <algorithm>
#include <numeric>

NPDBasketPut::NPDBasketPut(double strike, std::vector<double> weights)
	:NPDBasket(strike, weights)
{

}

std::vector<std::vector<double>> NPDBasketPut::operator()(std::vector<std::vector<std::vector<double>>> x)
{
	if (len_weights > x[0].size())
	{
		std::cout<<"WARNING: Please enter "<< len_weights << " Spot prices" << std::endl;
		std::cout<<"There are "<< len_weights - x[0].size() <<" Spot missing" <<std::endl;
		std::cout<<"Result output is wrong!!!"<< std::endl;
		return x[0];
	}
	if (len_weights < x[0].size())
	{
		
		std::cout<<"WARNING: Please enter "<< len_weights << " Spot prices" << std::endl;
		std::cout<<"There are "<< x[0].size()- len_weights <<" more spot than weights" <<std::endl;
		std::cout<<"Result output is wrong!!!"<< std::endl;
		return x[0];
	}
	if (len_weights == x[0].size())
	{
		std::vector<std::vector<double>> Values;
		Values.resize(x.size(), std::vector<double>(x[0].size()));
		
		for (int i = 0; i < x.size(); i++)
		{
			double m = 0;
			
			for (int j = 0; j < x[i].size(); j++)
			{
				m += NPD_weights[j]*x[i][j][0];
			}
			
			Values[i][0] = (m < NPD_strike)? NPD_strike - m: 0;
			
			// std::vector<double> m(len_weights);
			// std::transform( NPD_weights.begin(), NPD_weights.end(), x[i].begin(), m.begin(), std::multiplies<double>());
			// double sum = std::accumulate(m.begin(),m.end(),0.0);
		}
		return Values;
	}
}