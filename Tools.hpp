#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>

void mult_matrix(const std::vector<std::vector<double>>& M1, const std::vector<std::vector<double>>& M2, std::vector<std::vector<double>>& M3);
void transpose_matrix(const std::vector<std::vector<double>>& M1, std::vector<std::vector<double>>& M2);
void Cholesky(std::vector<std::vector<double>>& A);
void inv_sym_defpos(const std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& Ainv);

#endif