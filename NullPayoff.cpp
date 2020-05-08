#include "NullPayoff.hpp"

NullPayoff::NullPayoff()
{

}

std::vector<double> NullPayoff::operator()(const std::vector<std::vector<std::vector<double>>>& x) const
{

	std::vector<double> Values(x.size());
	return Values;
}
