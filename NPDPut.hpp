#ifndef NPDPUT_HPP
#define NPDPUT_HPP

#include "NonPathDependent.hpp"

class NPDPut :public NonPathDependent
{
	
public:
	NPDPut(double strike);
	
	virtual std::vector<std::vector<double>> operator()(std::vector<std::vector<std::vector<double>>> x);

};

#endif