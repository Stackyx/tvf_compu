#ifndef VANILLAPUT_HPP
#define VANILLAPUT_HPP


#include "Vanilla.hpp"


class VanillaPut :public Vanilla
{
	
public:
	VanillaPut(double strike);
	
	
	double operator()(double x);
	virtual double operator()(std::vector<double> x);

};

#endif