#include "VanillaCall.hpp"

VanillaCall::VanillaCall(double strike)
	:Vanilla(strike)
{
}


double VanillaCall::operator()(double x)
{
	return (x > V_strike)? x - V_strike : 0;
}

double VanillaCall::operator()(std::vector<double> x)
{
	return (x[0] > V_strike)? x[0] - V_strike : 0;
}