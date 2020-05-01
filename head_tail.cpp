#include "head_tail.hpp"
#include "pseudo_generator.hpp"

HeadTail::HeadTail(UniformGenerator* generator)
	: generator(generator), sum(0.)
{
}

double HeadTail::Generate()
{
	if (generator->Generate() < 0.5)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}
