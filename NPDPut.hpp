#ifndef NPDPUT_HPP
#define NPDPUT_HPP

#include "NonPathDependent.hpp"

class NPDPut :public NonPathDependent
{
	
public:
	NPDPut(double strike, std::vector<double> weights);
	NPDPut(double strike);
	
	std::vector<double> get_weights();
	std::vector<double> operator()(const std::vector<std::vector<std::vector<double>>>& x) const;

private:
	std::vector<double> NPD_weights;
};

#endif