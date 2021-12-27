#include "libm.h"
#include "coreimpl.h"

double ceil(double x)
{
	return (double)rndint(x, 11);
}
