#include "VanDerCorput.hpp"
#include <iostream>
#include <cmath>

VanDerCorput::VanDerCorput(llong seed, llong base)
	: QuasiGenerator(seed), base(base)
{
}

double VanDerCorput::Generate()
{
    double vdc = 0, denom = 1;
    llong n(s);

    while (n > 0)
    {
        vdc += fmod(n, base) / (denom *= base);
        n /= base; // note: conversion from 'double' to 'int'
    }

    s += 1;
    return vdc;
}
