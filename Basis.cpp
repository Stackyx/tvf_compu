#include "Basis.hpp"

Basis::Basis(int number)
	:B_nb(number)
{

}


int factorial(int n)
{
    if(n > 1)
        return n * factorial(n - 1);
    else
        return 1;
}