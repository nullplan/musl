#include "libm.h"
#include "coreimpl.h"

long double atan2l(long double y, long double x)
{
	return atan2_core(y, x);
}
