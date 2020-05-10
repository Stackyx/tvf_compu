#include "NullPayoff.hpp"

NullPayoff::NullPayoff(double weights_size)
	:weights_sz(weights_size)
{

}

std::vector<double> NullPayoff::operator()(const std::vector<std::vector<std::vector<double>>>& x) const
{

	std::vector<double> Values(x.size());
	return Values;
}

std::vector<double> NullPayoff::operator()(const std::vector<std::vector<std::vector<double>>>& x, llong k) const
{

	std::vector<double> Values(x.size());
	return Values;
}

std::vector<double> NullPayoff::get_weights()
{
	std::vector<double> Values(weights_sz);
	return Values;
}