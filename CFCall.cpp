#include "CFCall.hpp"


CFCall::CFCall(double strike, std::vector<double> weights)
	:ClosedForm(strike), CF_weights(weights)
{
	
}

CFCall::CFCall(double strike)
	:ClosedForm(strike)
{
	CF_weights.push_back(1);
}

std::vector<double> CFCall::get_weights()
{
	return CF_weights;
}

double CFCall::operator()(const double& S0, const double& mu, const double& TTM, const double& vol) const
{
	double d1 = (std::log(S0/CF_strike) + (mu + 0.5*vol*vol)*TTM)/(vol*std::sqrt(TTM));
	double d2 = d1 - (vol*std::sqrt(TTM));
	
	return CF_weights[0] *(S0*normalCDF(d1) - CF_strike*std::exp(-mu*TTM)*normalCDF(d2));
}
	
std::vector<double> CFCall::operator()(const std::vector<std::vector<std::vector<double>>>& x) const
{
	throw std::runtime_error("Error, operator not applicable for closed form formula");

}