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
	virtual std::vector<double> Generate(llong n);
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