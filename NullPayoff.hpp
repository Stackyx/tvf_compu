#pragma once
#include "NonPathDependent.hpp"

class NullPayoff : public NonPathDependent
{
public:
	NullPayoff(double weights_size);
	std::vector<double> operator()(const std::vector<std::vector<std::vector<double>>>& x) const;
	std::vector<double> operator()(const std::vector<std::vector<std::vector<double>>>& x, const int& k) const;
	std::vector<double> get_weights();
	
private:
	double weights_sz;
};

