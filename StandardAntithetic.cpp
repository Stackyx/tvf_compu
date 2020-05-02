#include "StandardAntithetic.hpp"
#include <iostream>
double StandardAntithetic::operator()(double X, double mu, double sigma) const
{
	return 2 * mu - X;
}

std::vector<std::vector<double>> StandardAntithetic::operator()(const std::vector<std::vector<double>>& X, double mu, double sigma) const
{
	std::vector<std::vector<double>> Y(X);
	
	for (llong i = 0; i < Y.size(); ++i)
	{
		for (llong j = 0; j < Y[i].size(); ++j)
		{
			Y[i][j] = 2 * mu - Y[i][j];
		}
	}

	return Y;
}
