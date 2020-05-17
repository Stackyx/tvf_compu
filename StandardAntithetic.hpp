#pragma once
#include "R3R1Function.hpp"

// This class allows to apply the transformation needed when doing the Antithetic variance reduction method.

class StandardAntithetic : public R3R1Function
{
public:
	double operator()(double X, double mu, double sigma) const;
	std::vector<std::vector<double>> operator()(const std::vector<std::vector<double>>& X, double mu, double sigma) const;
	void operator()(std::vector<std::vector<double>>& X_transform, const std::vector<std::vector<double>>& X, double mu, double sigma);

};

