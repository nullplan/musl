#include "libm.h"

long double ldexpl(long double x, int e)
{
	return scalbnl(x, e);
}

