#include "NPDBasket.hpp"

NPDBasket::NPDBasket(double strike, std::vector<double> weights)
	:NonPathDependent(strike), NPD_weights(weights)
{
	len_weights = NPD_weights.size();
}
