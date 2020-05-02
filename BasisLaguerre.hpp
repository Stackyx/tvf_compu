#ifndef BASISLAGUERRE_HPP
#define BASISLAGUERRE_HPP

#include "Basis.hpp"
class BasisLaguerre : public Basis
{
	
public:
	BasisLaguerre(int number);
	
	virtual double get_Lk(const double& X);
	

};


#endif