#ifndef BASIS_HPP
#define BASIS_HPP

#include <string>
#include <vector>
#include <iostream>

typedef unsigned long long llong;

class Basis
{
public:
	
	Basis(llong number);
	
	virtual double get_Lk(double X) = 0;
	virtual std::vector<std::vector<double>> get_matrix_L(const std::vector<double>& X) = 0;
	
protected:
	llong B_nb;
};

#endif