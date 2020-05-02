#include "PDBasketCall.hpp"
#include <algorithm>
#include <numeric>

PDBasketCall::PDBasketCall(double strike, std::vector<double> weights)
	:PDBasket(strike, weights)
{

}

std::vector<double> PDBasketCall::operator()(const std::vector<std::vector<std::vector<double>>>& x) const
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
		
		for (int i = 0; i < x.size(); i++)
		{
			double m = 0;
			
			for (int j = 0; j < x[i].size(); j++)
			{
				m += PD_weights[j]*x[i][j][x[i][j].size()-1];
			}
			
			Values[i] = (m > PD_strike)? m - PD_strike : 0;
		}

		return Values;
	}
}


std::vector<double> PDBasketCall::operator()(const std::vector<std::vector<std::vector<double>>>& x, const int& k) const
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
		
		for (int i = 0; i < x.size(); i++)
		{
			double m = 0;
			
			for (int j = 0; j < x[i].size(); j++)
			{
				m += PD_weights[j]*x[i][j][k];
			}
			
			Values[i] = (m > PD_strike)? m - PD_strike : 0;
		}

		return Values;
	}
}