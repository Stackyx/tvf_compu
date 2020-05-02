#include "Tools.hpp"

void mult_matrix(const std::vector<std::vector<double>>& M1, const std::vector<std::vector<double>>& M2, std::vector<std::vector<double>>& M3)
{
	if (M1[0].size() != M2.size())
	{
		throw std::runtime_error("You try to multiply 2 matrix with row and size not matching.");
	}
	
	M3.resize(M1.size(), std::vector<double>(M2[0].size())); 
	
	for (int i=0; i<M1.size();i++)
	{
		for(int j=0; j< M2[0].size();j++)
		{
			for(int k=0; k<M1[0].size(); k++)
			{
				M3[i][j] += M1[i][k] * M2[k][j];
			}
		}
		
	}
	
}

void transpose_matrix(const std::vector<std::vector<double>>& M1, std::vector<std::vector<double>>& M2)
{
	M2.resize(M1[0].size(), std::vector<double>(M1.size()));
	for (int i = 0; i<M1.size(); i++)
	{
		for (int j = 0; j<M1[0].size(); j++)
		{
			M2[j][i] = M1[i][j];
		}
	}
}


void Cholesky(std::vector<std::vector<double>>& A)
{
	long i, j, k;
	std::vector<double> tmp;
	double sum;
	
	if (A[0].size() != A.size()) throw("need square matrix");
	
	for (i = 0; i < A.size(); i++) {
		for (j = i; j < A.size(); j++) {
			for (sum = A[i][j], k = i - 1; k >= 0; k--) 
			{
				sum -= A[i][k] * A[j][k];
			}
			if (i == j) 
			{
				if (sum <= 0.0)
				{
					throw("Cholesky failed.");
				}
				A[i][i] = sqrt(sum);
			}
			else A[j][i] = sum / A[i][i];
		}
	}
	for (i = 0; i < A.size(); i++) for (j = 0; j < i; j++) A[j][i] = 0.;
	
}

void inv_sym_defpos(const std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& Ainv)
{
	long i, j, k;
	std::vector<double> tmp;
	double sum;
	
	std::vector<std::vector<double>> A_copy(A);
	Cholesky(A_copy);
	
	Ainv.resize(A_copy.size(), std::vector<double>(A_copy[0].size()));
	
	for (i=0;i<A_copy.size();i++) for (j=0;j<=i;j++)
	{
		sum = (i==j? 1. : 0.);
		for (k=i-1; k>=j; k--) 
		{
			sum -= A_copy[i][k]*Ainv[j][k];
		}
		Ainv[j][i]= sum/A_copy[i][i];
	}
	
	for (i=A_copy.size()-1;i>=0;i--) for (j=0;j<=i;j++)
	{
		sum = (i<j? 0. : Ainv[j][i]);
		
		for (k=i+1; k<A_copy.size(); k++) 
		{
			sum -= A_copy[k][i]*Ainv[j][k];
		}
		Ainv[i][j] = Ainv[j][i] = sum/A_copy[i][i];
	}


}


