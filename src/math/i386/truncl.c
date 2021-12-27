#include "libm.h"
#include "coreimpl.h"
long double truncl(long double x)
{
	return rndint(x, 15);
}
