#include "random_generator.hpp"
#include <fstream>

RandomGenerator::RandomGenerator()
{
}

RandomGenerator::~RandomGenerator()
{
}

std::vector<double> RandomGenerator::Generate(llong n)
{
	throw std::runtime_error("Vector generate not implemented");
}

double RandomGenerator::Mean(llong nbSims)
{
	mean = 0;
	for (llong i = 0; i < nbSims; ++i)
	{
		mean += Generate() / nbSims;
	}
	meanComputed = true;

	return mean;
}

double RandomGenerator::Var(llong nbSims)
{
	double x;
	var = 0;
	if (meanComputed)
	{
		for (llong i = 0; i < nbSims; ++i)
		{
			x = Generate();
			var += (x - mean) * (x - mean) / (nbSims - 1);
		}
	}
	else
	{
		mean = Mean(10000000);
		for (llong i = 0; i < nbSims; ++i)
		{
			x = Generate();
			var += (x - mean) * (x - mean) / (nbSims - 1);
		}
	}
	return var;
}

void RandomGenerator::export_csv(llong nbSims, std::string f_name)
{
	std::ofstream f;
	f.open(f_name);

	for (llong i = 0; i < nbSims; ++i)
	{
		f << Generate() << "\n";
	}

	f.close();
}

llong RandomGenerator::getCurrent() const
{
	return current;
}


