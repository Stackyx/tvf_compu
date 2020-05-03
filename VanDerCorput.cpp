#include "VanDerCorput.hpp"
#include <iostream>
#include <cmath>

VanDerCorput::VanDerCorput(llong seed, llong base)
	: QuasiGenerator(seed), base(base)
{
}

double VanDerCorput::Generate()
{
	llong n = s;
	double q = 0.;
	double bk = (double)1 / base;

	while (n > 0)
	{
		q += (n % base) * bk;
		// std::cout << "modula =  " << n % base << std::endl;
		// std::cout << "q =  " << q << std::endl;
		n /= base;
		// std::cout << "n = " << n << std::endl;
		bk /= base;
		// std::cout << "bk = " << bk << std::endl;
	}

	s += 1;
	return q;
}
