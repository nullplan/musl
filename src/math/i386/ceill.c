#include "libm.h"
#include "coreimpl.h"

long double ceill(long double x)
{
	return rndint(x, 11);
}
