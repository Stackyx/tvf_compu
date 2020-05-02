#include "BasisLaguerre.hpp"

BasisLaguerre::BasisLaguerre(int number)
	:Basis(number)
{
}

double BasisLaguerre::get_Lk(const double& X)
{
	double L = 0;
	for (int i = 0; i<=B_nb; ++i)
	{
		L += factorial(B_nb)/(factorial(i)*factorial(B_nb-i)) * std::pow(-1, i)/factorial(i) * std::pow(X, i);
	}
	return L;
}
