#include "PDCall.hpp"


PDCall::PDCall(double strike, std::vector<double> weights)
	:PathDependent(strike), PD_weights(weights)
{
	
}

PDCall::PDCall(double strike)
	:PathDependent(strike)
{
	PD_weights.push_back(1);
}

std::vector<double> PDCall::get_weights()
{
	return PD_weights;
}
	
	
std::vector<double> PDCall::operator()(const std::vector<std::vector<std::vector<double>>>& x) const
{
	
	std::vector<double> Values;
	Values.resize(x.size());
	
	for (int i = 0; i < x.size(); i++)
	{

		double m =  PD_weights[0]*x[i][0][x[0][0].size()-1];
		
		Values[i] = (m > PD_strike)? m - PD_strike : 0;
	}

	return Values;

}

std::vector<double> PDCall::operator()(const std::vector<std::vector<std::vector<double>>>& x, const int& k) const
{
	
	std::vector<double> Values;
	Values.resize(x.size());
	
	for (int i = 0; i < x.size(); i++)
	{

		double m =  PD_weights[0]*x[i][0][k];
		
		Values[i] = (m > PD_strike)? m - PD_strike : 0;
	}

	return Values;

}




