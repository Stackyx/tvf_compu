#ifndef CLOSEDFORM_HPP
#define CLOSEDFORM_HPP

#include "Payoff.hpp"
class ClosedForm : public Payoff
{
public:
	ClosedForm(double strike);
	virtual double operator()(const double& S0, const double& mu, const double& TTM, const double& vol) const = 0;
protected:
	double CF_strike;
};

#endif