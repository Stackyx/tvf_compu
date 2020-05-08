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
		
		// std::cout<<"----------time "<<k<<" -----------"<<std::endl;
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
		inv_sym_defpos(A, Ainv);
		
		std::vector<std::vector<double>> CC;
		mult_matrix(A, Ainv, CC);
		// display_mat(CC);
		// std::cout<<std::endl;
		
		mult_matrix(Ainv,LT,C);
		mult_matrix_vect(C, Y, Beta);

		//compute continuous value
		std::vector<double> C_hat;
		mult_matrix_vect(L, Beta, C_hat);
		std::vector<double> G((*LSM_payoff)(S, k));
		int c = 0;
		
		for (int i = 0; i<P.size(); i++)
		{
			if (itm_path[i] == 1)
			{

				// std::cout<< "Spot = "<<X[c]<< ", G(S(t)) = "<< G[i] <<", C_hat = "<<C_hat[c]<<std::endl;
				if (G[i]>C_hat[c])
				{
					P[i] = G[i];
				}
				c +=1;
			}
			else
			{
				P[i] = std::exp(-r*dt)*P[i];
			}
			
		}

	}
	price = std::exp(-r*dt)*std::accumulate(P.begin(), P.end(), 0.0)/(P.size());
}

void MonteCarloLSM::Solve(Payoff* MC_payoff_CV, double ClosedFormValue)
{
	throw std::runtime_error("Please enter a PathDependent payoff");
}

void MonteCarloLSM::Solve(PathDependent* MC_payoff_CV, double ClosedFormValue)
{
	
	std::vector<std::vector<std::vector<double>>> S(mc_stocks->Generate(N_sims));
	
	std::vector<double> P((*LSM_payoff)(S, S[0][0].size()-1));
	std::vector<double> itm_path(P.size());
	std::vector<double> Weights(LSM_payoff->get_weights());
	
	std::vector<double> P2((*MC_payoff_CV)(S, S[0][0].size()-1));
	std::vector<double> itm_path2(P2.size());
	std::vector<double> Weights2(MC_payoff_CV->get_weights());

	price = 0;
	double price2 = 0;
	size_t nb_steps = S[0][0].size();
	double dt = (mc_stocks->get_maturity())/(nb_steps-1);
	double r = mc_stocks->get_mu();
	
	
	for (int k = nb_steps-2; k>0; k--)
	{
		std::vector<double> X;
		std::vector<double> Y;
		
		std::vector<double> X2;
		std::vector<double> Y2;
		
		// std::cout<<"----------time "<<k<<" -----------"<<std::endl;
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
			
			
			if (P2[i]>0)
			{
				itm_path2[i] = 1;
				double xi = 0;
				for (int j = 0; j<Weights2.size(); j++)
				{
					xi += Weights2[j]*S[i][j][k];
				}
				X2.push_back(xi);
				Y2.push_back(std::exp(-r * dt)*P2[i]);
			}
			else
			{
				itm_path2[i] = 0;
			}
			
		}

		// regression
		std::vector<std::vector<double>> L(LSM_Basis->get_matrix_L(X));
		std::vector<std::vector<double>> LT;
		std::vector<std::vector<double>> A;
		std::vector<std::vector<double>> Ainv;
		std::vector<std::vector<double>> C;
		std::vector<double> Beta;
		
		std::vector<std::vector<double>> L2(LSM_Basis->get_matrix_L(X2));
		std::vector<std::vector<double>> L2T;
		std::vector<std::vector<double>> A2;
		std::vector<std::vector<double>> Ainv2;
		std::vector<std::vector<double>> C2;
		std::vector<double> Beta2;

		transpose_matrix(L, LT);
		transpose_matrix(L2, L2T);
		
		mult_matrix(LT,L,A);
		mult_matrix(L2T,L2,A2);
		
		inv_sym_defpos(A, Ainv);
		inv_sym_defpos(A2, Ainv2);
		
		std::vector<std::vector<double>> CC;
		std::vector<std::vector<double>> CC2;
		mult_matrix(A, Ainv, CC);
		mult_matrix(A2, Ainv2, CC2);
		
		mult_matrix(Ainv,LT,C);
		mult_matrix(Ainv2,L2T,C2);
		mult_matrix_vect(C, Y, Beta);
		mult_matrix_vect(C2, Y2, Beta2);

		//compute continuous value
		std::vector<double> C_hat;
		std::vector<double> C_hat2;
		mult_matrix_vect(L, Beta, C_hat);
		mult_matrix_vect(L2, Beta2, C_hat2);
		std::vector<double> G((*LSM_payoff)(S, k));
		std::vector<double> G2((*MC_payoff_CV)(S, k));
		
		
		
		int c = 0;
		int c2 = 0;
		
		for (int i = 0; i<P.size(); i++)
		{
			if (itm_path[i] == 1)
			{

				// std::cout<< "Spot = "<<X[c]<< ", G(S(t)) = "<< G[i] <<", C_hat = "<<C_hat[c]<<std::endl;
				if (G[i]>C_hat[c])
				{
					P[i] = G[i];
				}
				c +=1;
			}
			else
			{
				P[i] = std::exp(-r*dt)*P[i];
			}
			
			
			if (itm_path2[i] == 1)
			{

				// std::cout<< "Spot = "<<X[c]<< ", G(S(t)) = "<< G[i] <<", C_hat = "<<C_hat[c]<<std::endl;
				if (G2[i]>C_hat2[c])
				{
					P2[i] = G2[i];
				}
				c2 +=1;
			}
			else
			{
				P2[i] = std::exp(-r*dt)*P2[i];
			}
			
		}

	}
	price2 = std::exp(-r*dt)*std::accumulate(P2.begin(), P2.end(), 0.0)/(P2.size());
	price = std::exp(-r*dt)*std::accumulate(P.begin(), P.end(), 0.0)/(P.size());
	
	price = price + (ClosedFormValue - price2);
}


void display_mat(const std::vector<std::vector<double>>& A)
{
	for (int ii =0; ii<A.size();++ii)
	{
		for(int jj = 0; jj<A[0].size(); ++jj)
		{
			std::cout<<A[ii][jj]<<", ";
		}
		std::cout<<std::endl;
	}
	
}

void display_vect(const std::vector<double>& A)
{
	for (int ii =0; ii<A.size();++ii)
	{

		std::cout<<A[ii]<<", ";
		
	}
	std::cout<<std::endl;
	
}

