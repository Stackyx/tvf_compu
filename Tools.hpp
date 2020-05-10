#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <iostream>

void mult_matrix(const std::vector<std::vector<double>>& M1, const std::vector<std::vector<double>>& M2, std::vector<std::vector<double>>& M3);
void mult_matrix_vect(const std::vector<std::vector<double>>& M1, const std::vector<double>& V1, std::vector<double>& V2);
void transpose_matrix(const std::vector<std::vector<double>>& M1, std::vector<std::vector<double>>& M2);
void Cholesky(std::vector<std::vector<double>>& A);
void inv_sym_defpos(const std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& Ainv);
int factorial(int n);

void getCofactor(const std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& temp, int p, int q, int n);
double determinant(const std::vector<std::vector<double>>& A, int n);
void adjoint(const std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& adj);
bool inverse(const std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& inv);

double normalCDF(double value);

void display_mat(const std::vector<std::vector<double>>& A);
void display_vect(const std::vector<double>& A);

#endif