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

void mult_matrix_vect(const std::vector<std::vector<double>>& M1, const std::vector<double>& V1, std::vector<double>& V2)
{
	if (M1[0].size() != V1.size())
	{
		throw std::runtime_error("You try to multiply a matrix and vector with size not matching.");
	}
	
	V2.resize(M1.size()); 
	
	for (int i=0; i<M1.size();i++)
	{
		for(int j=0; j< M1[0].size();j++)
		{
				V2[i] += M1[i][j] * V1[j];
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
	double sum;

	if (A[0].size() != A.size()) throw("need square matrix");
	
	for (i = 0; i < A.size(); i++) {
		for (j = i; j < A.size(); j++) {

			for (sum = A[i][j], k = i - 1; k > -1; k--) 
			{
				
				sum -= A[i][k] * A[j][k];
			}
			if (i == j) 
			{
				if (sum <= 0.0)
				{
					std::cout<<sum;
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

int factorial(int n)
{
    if(n > 1)
        return n * factorial(n - 1);
    else
        return 1;
}


void inverse(const std::vector<std::vector<double>>& A ,std::vector<std::vector<double>>& D,double det)
{
	int n = A.size();
	if(det == 0)
	{
		std::cout<<"\nInverse of Entered Matrix is not possible\n";
	}
	else if(n == 1)
	{
		D[0][0] = 1;
	}
	else
		cofactor(A,D,det);
}


void cofactor(const std::vector<std::vector<double>>& A ,std::vector<std::vector<double>>& D,double deter)
{
	std::vector<std::vector<double>> B;
	std::vector<std::vector<double>> C;
	int l,h,m,k,i,j;
	
	for (h=0;h<A.size();h++)
	{
		for (l=0;l<A.size();l++)
		{
			m=0;
			k=0;
			for (i=0;i<A.size();i++)
			{
				for (j=0;j<A.size();j++)
				{
					if (i != h && j != l)
					{
						B[m][k]=A[i][j];
						if (k<(A.size()-2))
						{
							k++;
						}
						else
						{
							k=0;
							m++;
						}
					}
				}
			}
			C[h][l] = (double) std::pow(-1,(h+l))*det(B);	// c = cofactor Matrix
		}
	}
	transpose_matrix(C,D);//pas sur de det 
}

double det(const std::vector<std::vector<double>>& A )
{
	int i;
	double sum = 0;
	std::vector<std::vector<double>> B;
	
	if (A.size() == 1)
		return A[0][0];
	else if(A.size() == 2)
		return (A[0][0]*A[1][1]-A[0][1]*A[1][0]);
	else
		for(i=0;i<A.size();i++)
		{
			minor(B,A,i);
			sum = (double) (sum + A[0][i]*pow(-1,i)*det(B));	// sum = determinte matrix
		}
	return sum;
}

void minor(std::vector<std::vector<double>>& B,const std::vector<std::vector<double>>& A,int i)
{
	int h=0,k=0;
	
	for( int l=1; l<A.size(); l++)
	{
		for( int j=0; j<A.size(); j++)
		{
			if(j == i)
				continue;
			B[h][k] = A[l][j];
			k++;
			if(k == (A.size()-1)){
				h++;
				k=0;
			}
		}
	}
}