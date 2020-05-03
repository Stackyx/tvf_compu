#ifndef RANDOM_GENERATOR_HPP
#define RANDOM_GENERATOR_HPP
#include <string>
#include <vector>

typedef unsigned long long llong;

class RandomGenerator
{
	
public:
	RandomGenerator();
	~RandomGenerator();
	
	virtual double Generate() = 0;

	virtual std::vector<std::vector<double>> Generate(llong n);
	virtual void Generate(std::vector<std::vector<double>>& W, llong n);

	virtual std::vector<std::vector<double>> get_covariance_matrix();

	double Mean(llong nbSims);
	double Var(llong nbSims);
	void export_csv(llong nbSims, std::string f_name);

	llong getCurrent() const;

protected:
	llong current;

private:
	bool meanComputed = false;
	double mean = 0;
	double var = 0;
};

#endif