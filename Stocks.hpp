#pragma once
#include <vector>

typedef unsigned long long llong;

class Stocks
{
public:
	virtual std::vector<std::vector<std::vector<double>>> Generate(llong n_sims) = 0;
private:

};

