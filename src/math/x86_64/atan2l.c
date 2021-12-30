#include "libm.h"
#include "x87.h"

long double atan2l(long double y, long double x)
{
	return x87_fpatan(x, y);
}
