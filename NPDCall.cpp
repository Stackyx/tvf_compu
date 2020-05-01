#include "NPDCall.hpp"

NPDCall::NPDCall(double strike)
	:NonPathDependent(strike)
{
}


std::vector<std::vector<double>> NPDCall::operator()(std::vector<std::vector<std::vector<double>>> x)
{
	std::vector<std::vector<double>> Values;
	Values.resize(x.size(), std::vector<double>(x[0].size())); 
	
	for (int i = 0; i < x.size(); i++)
	{
		for (int j = 0; j < x[i].size(); j++)
		{
			Values[i][j] = (x[i][j][0]  > NPD_strike)? x[i][j][0] - NPD_strike : 0;
		}
	}
		
	return Values;
}