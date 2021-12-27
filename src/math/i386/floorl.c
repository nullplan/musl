#include "libm.h"
#include "coreimpl.h"
long double floorl(long double x)
{
	return rndint(x, 7);
}
