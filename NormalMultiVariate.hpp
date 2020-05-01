#pragma once
#include "ContinuousGenerator.hpp"
#include "uniform_generator.hpp"
#include "Normal.hpp"

class NormalMultiVariate : public ContinuousGenerator
{
public:
	NormalMultiVariate(UniformGenerator* gen, std::vector<double> mu, std::vector<double> sigma, double corr);
	NormalMultiVariate(UniformGenerator* gen, std::vector<double> mu, std::vector<double> sigma, std::vector<std::vector<double>> corr);
	std::vector<double> Generate(llong n);
	double Generate();

private:
	UniformGenerator* gen;
	ContinuousGenerator* norm_gen;

	std::vector<double> mu;
	std::vector<double> sigma;

	double corr;
	std::vector<std::vector<double>> m_corr;

};

