#pragma once
#include "NonPathDependent.hpp"

class NullPayoff : public NonPathDependent
{
public:
	NullPayoff(llong weights_size);
	std::vector<double> operator()(const std::vector<std::vector<std::vector<double>>>& x) const;
	std::vector<double> operator()(const std::vector<std::vector<std::vector<double>>>& x, llong k) const;
	std::vector<double> get_weights();
	
private:
	llong weights_sz;
};

