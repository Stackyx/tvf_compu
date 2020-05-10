#ifndef BASISLAGUERRE_HPP
#define BASISLAGUERRE_HPP

#include "Basis.hpp"
#include "Tools.hpp"

class BasisLaguerre : public Basis
{
	
public:
	BasisLaguerre(llong number);
	
	virtual double get_Lk(double X);
	double get_Lk(double X, llong k);
	virtual std::vector<std::vector<double>> get_matrix_L(const std::vector<double>& X);

};


#endif