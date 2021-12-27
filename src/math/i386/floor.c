#include "libm.h"
#include "coreimpl.h"

double floor(double x)
{
	return (double)rndint(x, 7);
}
