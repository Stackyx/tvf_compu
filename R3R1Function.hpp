#pragma once
#include <vector>
#include <stdexcept>
typedef unsigned long long llong;

class R3R1Function
{
public:
	virtual double operator()(double X, double mu, double sigma) const = 0;
	virtual std::vector<std::vector<double>> operator()(const std::vector<std::vector<double>>& X, double mu, double sigma) const = 0;
	void operator()(std::vector<std::vector<double>>& X_transform, const std::vector<std::vector<double>>& X, double mu, double sigma);
};

