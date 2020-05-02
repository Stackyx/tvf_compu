#include "NPDBasketPut.hpp"
#include <algorithm>
#include <numeric>

NPDBasketPut::NPDBasketPut(double strike, std::vector<double> weights)
	:NPDBasket(strike, weights)
{

}

std::vector<double> NPDBasketPut::operator()(const std::vector<std::vector<std::vector<double>>>& x) const
{
	if (len_weights > x[0].size())
	{
		throw std::runtime_error("You entered too many weights. Exiting.");
	}
	if (len_weights < x[0].size())
	{
		throw std::runtime_error("Not enough weights for the number of assets. Exiting.");
	}
	else
	{
		std::vector<double> Values;
		Values.resize(x.size());
		
		double m(0);

		for (int i = 0; i < x.size(); i++)
		{			
			m = 0;

			for (int j = 0; j < x[i].size(); j++)
			{
				m += NPD_weights[j]*x[i][j][0];
			}
			
			Values[i] = (m < NPD_strike)? NPD_strike - m: 0;
			
			// std::vector<double> m(len_weights);
			// std::transform( NPD_weights.begin(), NPD_weights.end(), x[i].begin(), m.begin(), std::multiplies<double>());
			// double sum = std::accumulate(m.begin(),m.end(),0.0);
		}
		return Values;
	}
}