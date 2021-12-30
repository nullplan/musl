#include "libm.h"
#include "x87.h"

long double log10l(long double x)
{
	return x87_fyl2x(x, x87_lg2());
}
