#include "Payoff.hpp"

std::vector<double> Payoff::get_weights()
{
	throw std::runtime_error("This payoff class has no weights.");
}
