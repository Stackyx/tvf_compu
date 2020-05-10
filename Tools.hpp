#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <iostream>

typedef unsigned long long llong;

void mult_matrix(const std::vector<std::vector<double>>& M1, const std::vector<std::vector<double>>& M2, std::vector<std::vector<double>>& M3);
void mult_matrix_vect(const std::vector<std::vector<double>>& M1, const std::vector<double>& V1, std::vector<double>& V2);
void transpose_matrix(const std::vector<std::vector<double>>& M1, std::vector<std::vector<double>>& M2);
void Cholesky(std::vector<std::vector<double>>& A);
void inv_sym_defpos(const std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& Ainv);
llong factorial(llong n);

void getCofactor(const std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& temp, llong p, llong q, llong n);
double determinant(const std::vector<std::vector<double>>& A, llong n);
void adjoint(const std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& adj);
bool inverse(const std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& inv);

double normalCDF(double value);

void display_mat(const std::vector<std::vector<double>>& A);
void display_vect(const std::vector<double>& A);

#endif