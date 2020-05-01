#ifndef discrete
#define discrete

#include "random_generator.hpp"

class DiscreteGenerator : public RandomGenerator
{
public:
	virtual void print_cumul();
};	

#endif