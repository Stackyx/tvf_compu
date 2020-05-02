#include "PDBasket.hpp"

PDBasket::PDBasket(double strike, std::vector<double> weights)
	:PathDependent(strike), PD_weights(weights)
{
	len_weights = PD_weights.size();
}

std::vector<double> PDBasket::get_weights()
{
	return PD_weights;
}