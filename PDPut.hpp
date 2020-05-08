#ifndef PDPUT_HPP
#define PDPUT_HPP

#include "PathDependent.hpp"

class PDPut :public PathDependent
{
	
public:
	PDPut(double strike, std::vector<double> weights);
	PDPut(double strike);
	
	std::vector<double> get_weights();
	std::vector<double> operator()(const std::vector<std::vector<std::vector<double>>>& x) const;
	std::vector<double> operator()(const std::vector<std::vector<std::vector<double>>>& x, const int& k) const;

private:
	std::vector<double> PD_weights;
};

#endif