#include "libm.h"
#include "x87.h"

long double floorl(long double x)
{
	return x87_frndint_rm(x, 7);
}
