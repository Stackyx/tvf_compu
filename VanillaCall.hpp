#ifndef VANILLACALL_HPP
#define VANILLACALL_HPP

#include "Vanilla.hpp"

class VanillaCall :public Vanilla
{
	
public:
	VanillaCall(double strike);
	
	
	double operator()(double x);
	virtual double operator()(std::vector<double> x);

};

#endif