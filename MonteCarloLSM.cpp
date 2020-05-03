#include "MonteCarloLSM.hpp"
#include <algorithm>
#include <numeric>
#include <iomanip>

MonteCarloLSM::MonteCarloLSM(StocksFullPath* stocks, PathDependent* payoff, llong n_sims, Basis* BasisFunction)
	: MonteCarlo(stocks, payoff, n_sims), LSM_Basis(BasisFunction), LSM_payoff(payoff)
{
}

void MonteCarloLSM::Solve()
{
	std::streamsize prec=std::cout.precision();
	
	std::vector<std::vector<std::vector<double>>> S(mc_stocks->Generate(N_sims));
	std::vector<double> P((*LSM_payoff)(S, S[0][0].size()-1));
	std::vector<double> itm_path(P.size());
	std::vector<double> Weights(LSM_payoff->get_weights());

	price = 0;
	size_t nb_steps = S[0][0].size();
	double dt = (mc_stocks->get_maturity())/(nb_steps-1);
	double r = mc_stocks->get_mu();
	
	for (int k = nb_steps-2; k>0; k--)
	{
		std::vector<double> X;
		std::vector<double> Y;

		for(int i = 0; i<P.size(); i++)
		{
			//seperate the path in the money
			if (P[i]>0)
			{
				itm_path[i] = 1;
				double xi = 0;
				for (int j = 0; j<Weights.size(); j++)
				{
					xi += Weights[j]*S[i][j][k];
				}
				X.push_back(xi);
				Y.push_back(std::exp(-r * dt)*P[i]);
			}
			else
			{
				itm_path[i] = 0;
			}
		}

		// regression
		std::vector<std::vector<double>> L(LSM_Basis->get_matrix_L(X));
		std::vector<std::vector<double>> LT;
		std::vector<std::vector<double>> A;
		std::vector<std::vector<double>> Ainv;
		std::vector<std::vector<double>> C;
		std::vector<double> Beta;
		

		transpose_matrix(L, LT);
		mult_matrix(LT,L,A);
		std::cout<<"dim A: ("<<A.size()<<", "<<A[0].size()<<"), ";
		 // dim Ainv: ("<<Ainv.size()<<", "<<Ainv[0].size()<<"), "
		if (k ==3)
		{
		for (int ii =0; ii<A.size();++ii)
		{
			for(int jj = 0; jj<A[0].size(); ++jj)
			{
				std::cout<< std::setprecision(4)<<A[ii][jj]<<std::setprecision(prec)<<", ";
			}
			std::cout<<std::endl;
		}
		}
		inv_sym_defpos(A, Ainv);
		std::cout<<"OK3, ";
		mult_matrix(Ainv,LT,C);

		mult_matrix_vect(C, Y, Beta);

		//compute continuous value
		std::vector<double> C_hat;
		mult_matrix_vect(L, Beta, C_hat);
		std::vector<double> G((*LSM_payoff)(S, k));
		int c = 0;
		for (int i = 0; i<P.size(); i++)
		{
			if ((itm_path[i] == 1)&&(G[i]>C_hat[c]))
			{
				c +=1;
				P[i] = G[i];
			}
			else
			{
				P[i] = std::exp(-r*dt)*P[i];
			}
			
		}
		std::cout<<k<<std::endl;
	}
	price = std::exp(-r*dt)*std::accumulate(P.begin(), P.end(), 0.0)/(P.size());
}




