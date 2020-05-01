#include "pseudo_generator.hpp"

PseudoGenerator::PseudoGenerator()
	: seed(0)
{
	current = 0;
}

PseudoGenerator::PseudoGenerator(llong s)
	: seed(s)
{
	current = s;
}

PseudoGenerator::~PseudoGenerator(){}
