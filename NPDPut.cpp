#include "NPDPut.hpp"


NPDPut::NPDPut(double strike, std::vector<double> weights)
	:NonPathDependent(strike), NPD_weights(weights)
{
	
}

NPDPut::NPDPut(double strike)
	:NonPathDependent(strike)
{
	NPD_weights.push_back(1);
}

std::vector<double> NPDPut::get_weights()
{
	return NPD_weights;
}
	
	
std::vector<double> NPDPut::operator()(const std::vector<std::vector<std::vector<double>>>& x) const
{
	
	std::vector<double> Values;
	Values.resize(x.size());
	
	for (int i = 0; i < x.size(); i++)
	{

		double m =  NPD_weights[0]*x[i][0][x[0][0].size()-1];
		
		Values[i] = (m < NPD_strike)? NPD_strike - m: 0;
	}

	return Values;

}