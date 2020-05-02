#ifndef BASISLAGUERRE_HPP
#define BASISLAGUERRE_HPP

#include "Basis.hpp"
class BasisLaguerre : public Basis
{
	
public:
	BasisLaguerre(int number);
	
	virtual double get_Lk(const double& X);
	std::vector<std::vector<double>> get_matrix_L(const std::vector<double>& X, const int& k);

};


#endif