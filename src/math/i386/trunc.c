#include "libm.h"
#include "coreimpl.h"
double trunc(double x)
{
	return (double)rndint(x, 15);
}
