#include "PDPut.hpp"


PDPut::PDPut(double strike, std::vector<double> weights)
	:PathDependent(strike), PD_weights(weights)
{
	
}

PDPut::PDPut(double strike)
	:PathDependent(strike)
{
	PD_weights.push_back(1);
}

std::vector<double> PDPut::get_weights()
{
	return PD_weights;
}
	
	
std::vector<double> PDPut::operator()(const std::vector<std::vector<std::vector<double>>>& x) const
{
	
	std::vector<double> Values;
	Values.resize(x.size());
	
	for (int i = 0; i < x.size(); i++)
	{

		double m =  0;
		
		for (int j = 0; j<PD_weights.size(); j++)
		{
			m+= PD_weights[j]*x[i][j][x[0][j].size()-1];
		}
		
		Values[i] = (m < PD_strike)? PD_strike - m: 0;
	}

	return Values;

}


std::vector<double> PDPut::operator()(const std::vector<std::vector<std::vector<double>>>& x, const int& k) const
{
	
	std::vector<double> Values;
	Values.resize(x.size());
	
	for (int i = 0; i < x.size(); i++)
	{

		double m =  0;
		
		for (int j = 0; j<PD_weights.size(); j++)
		{
			m+= PD_weights[j]*x[i][j][k];
		}
		
		Values[i] = (m < PD_strike)? PD_strike - m: 0;
	}

	return Values;

}
