#ifndef BASIS_HPP
#define BASIS_HPP

#include <string>
#include <vector>
#include <iostream>

class Basis
{
public:
	
	Basis(int number);
	
	virtual double get_Lk(const double& X) = 0;
	
protected:
	int B_nb;
};

int factorial(int n);
#endif