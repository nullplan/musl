#include "libm.h"
#include "x87.h"

long double ceill(long double x)
{
	return x87_frndint_rm(x, 11);
}
