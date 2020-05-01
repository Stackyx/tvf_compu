#ifndef NPDCALL_HPP
#define NPDCALL_HPP

#include "NonPathDependent.hpp"

class NPDCall :public NonPathDependent
{
	
public:
	NPDCall(double strike);
	
	virtual std::vector<std::vector<double>> operator()(std::vector<std::vector<std::vector<double>>> x);

};

#endif