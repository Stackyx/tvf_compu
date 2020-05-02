#include "StocksTerminal.hpp"

StocksTerminal::StocksTerminal(ContinuousGenerator* Gen, double s0, double mu, double maturity)
	: Stocks(Gen, s0, mu, maturity)
{
}
