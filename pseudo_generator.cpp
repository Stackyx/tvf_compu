#include "pseudo_generator.hpp"

PseudoGenerator::PseudoGenerator(llong s)
	: seed(s), UniformGenerator(s)
{
	current = s;
}

