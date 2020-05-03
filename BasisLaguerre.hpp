#ifndef BASISLAGUERRE_HPP
#define BASISLAGUERRE_HPP

#include "Basis.hpp"
#include "Tools.hpp"

class BasisLaguerre : public Basis
{
	
public:
	BasisLaguerre(int number);
	
	virtual double get_Lk(const double& X);
	double get_Lk(const double& X, int k);
	virtual std::vector<std::vector<double>> get_matrix_L(const std::vector<double>& X);

};


#endif