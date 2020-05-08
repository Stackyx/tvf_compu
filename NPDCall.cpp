#include "NPDCall.hpp"


NPDCall::NPDCall(double strike, std::vector<double> weights)
	:NonPathDependent(strike), NPD_weights(weights)
{
	
}

NPDCall::NPDCall(double strike)
	:NonPathDependent(strike)
{
	NPD_weights.push_back(1);
}

std::vector<double> NPDCall::get_weights()
{
	return NPD_weights;
}
	
	
std::vector<double> NPDCall::operator()(const std::vector<std::vector<std::vector<double>>>& x) const
{
	
	std::vector<double> Values;
	Values.resize(x.size());
	
	for (int i = 0; i < x.size(); i++)
	{

		double m =  NPD_weights[0]*x[i][0][x[0][0].size()-1];
		
		Values[i] = (m > NPD_strike)? m - NPD_strike : 0;
	}

	return Values;

}