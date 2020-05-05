#ifndef CFPUT_HPP
#define CFPUT_HPP

#include "ClosedForm.hpp"
#include "Tools.hpp"

class CFPut :public ClosedForm
{
	
public:
	CFPut(double strike, std::vector<double> weights);
	CFPut(double strike);
	
	std::vector<double> get_weights();
	std::vector<double> operator()(const std::vector<std::vector<std::vector<double>>>& x) const;
	double operator()(const double& S0, const double& mu, const double& TTM, const double& vol) const;
	
private:
	std::vector<double> CF_weights;
};

#endif