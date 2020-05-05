#include "StocksFullPath.hpp"
#include <cmath>

StocksFullPath::StocksFullPath(ContinuousGenerator* gen, double s0, double mu, double maturity, llong n_steps)
	: Stocks(gen, s0, mu, maturity), N_steps(n_steps)
{
}

StocksFullPath::StocksFullPath(ContinuousGenerator* gen, double s0, double mu, double maturity, std::vector<double> divividends, std::vector<double> date_dividends, llong n_steps)
	: Stocks(gen, s0, mu, maturity), N_steps(n_steps), Div(divividends), Date_Div(date_dividends)
{
}
