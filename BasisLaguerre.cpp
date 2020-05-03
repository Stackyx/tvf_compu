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
		L += factorial(B_nb)/(factorial(i)*factorial(B_nb-i)) * std::pow(-1.0, i)/factorial(i) * std::pow(X, i);

	}

	return L;
}

double BasisLaguerre::get_Lk(const double& X, int k)
{

	double L = 0;
	for (int i = 0; i<=k; ++i)
	{
		L += factorial(k)/(factorial(i)*factorial(k-i)) * std::pow(-1.0, i)/factorial(i) * std::pow(X, i);

	}

	return L;
}


std::vector<std::vector<double>> BasisLaguerre::get_matrix_L(const std::vector<double>& X)
{
	std::vector<std::vector<double>> L;
	L.resize(X.size(), std::vector<double>(B_nb+1));

	for(int i = 0; i<X.size();++i)
	{
		for(int j = 0; j<=B_nb;++j)
		{
			L[i][j] = get_Lk(X[i], j);
			
		}
	}
	return L;
	
}