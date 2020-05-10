#include "Payoff.hpp"

std::vector<double> Payoff::get_weights()
{
	throw std::runtime_error("This payoff class has no weights.");
}

std::vector<double> Payoff::operator()(const std::vector<std::vector<std::vector<double>>>& x, llong k) const
{
	throw std::runtime_error("This payoff is not time dependent. You can't use this overload.");
}
