#pragma once
#include "QuasiGenerator.hpp"
class Sobol : public QuasiGenerator
{
public:
	Sobol(llong seed);
	double Generate();
	void sequence(int inputn);
private:


	bool simul;
	std::vector<double> x;
	int n;
	
};

