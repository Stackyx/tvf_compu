#pragma once
#include "uniform_generator.hpp"
class QuasiGenerator : public UniformGenerator
{
public:
	QuasiGenerator(llong seed);
protected:
	llong s;

};

