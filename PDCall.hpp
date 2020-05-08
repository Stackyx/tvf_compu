#ifndef PDCALL_HPP
#define PDCALL_HPP

#include "PathDependent.hpp"

class PDCall :public PathDependent
{
	
public:
	PDCall(double strike, std::vector<double> weights);
	PDCall(double strike);
	
	std::vector<double> get_weights();
	std::vector<double> operator()(const std::vector<std::vector<std::vector<double>>>& x) const;
	std::vector<double> operator()(const std::vector<std::vector<std::vector<double>>>& x, const int& k);

private:
	std::vector<double> PD_weights;
};

#endif