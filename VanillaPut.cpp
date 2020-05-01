#include "VanillaPut.hpp"

VanillaPut::VanillaPut(double strike)
	:Vanilla(strike)
{
}


double VanillaPut::operator()(double x)
{
	return (x < V_strike)? V_strike - x : 0;
}

double VanillaPut::operator()(std::vector<double> x)
{
	return (x[0] < V_strike)? V_strike - x[0] : 0;
}