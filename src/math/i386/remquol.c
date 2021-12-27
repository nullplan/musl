#include "libm.h"
#include "coreimpl.h"
long double remquol(long double a, long double b, int *quo)
{
	union ldshape ia = {a}, ib = {b};
	return remquo_core(a, b, quo, (ia.i.se ^ ib.i.se) >> 15);
}
