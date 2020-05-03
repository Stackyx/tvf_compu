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

#endif