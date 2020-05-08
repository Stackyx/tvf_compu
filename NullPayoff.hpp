#pragma once
#include "NonPathDependent.hpp"

class NullPayoff : public NonPathDependent
{
public:
	NullPayoff();
	std::vector<double> operator()(const std::vector<std::vector<std::vector<double>>>& x) const;
};

