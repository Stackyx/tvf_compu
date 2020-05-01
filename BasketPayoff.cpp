#include "BasketPayoff.hpp"

BasketPayoff::BasketPayoff(double strike, std::vector<double> weights)
	:Exotic(strike), E_weights(weights)
{
	len_weights = E_weights.size();
}
