#pragma once
#include "QuasiGenerator.hpp"
class VanDerCorput : public QuasiGenerator
{
public:
	VanDerCorput(llong seed, llong base);
	double Generate();
private:
	llong base;
};

