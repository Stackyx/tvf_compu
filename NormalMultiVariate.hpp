#ifndef NORMAL_MULTI_HPP
#define NORMAL_MULTI_HPP

#include "ContinuousGenerator.hpp"
#include "uniform_generator.hpp"
#include "Normal.hpp"

class NormalMultiVariate : public ContinuousGenerator
{
public:
	NormalMultiVariate(UniformGenerator* gen, const std::vector<double>& mu, const std::vector<std::vector<double>>& cov);
	double Generate();
	std::vector<std::vector<double>> Generate(llong n);
	std::vector<std::vector<double>> get_covariance_matrix();

private:
	ContinuousGenerator* norm_gen;

	const std::vector<double>& Mu;
	std::vector<std::vector<double>> L;
	const std::vector<std::vector<double>>& Cov;
};


#endif