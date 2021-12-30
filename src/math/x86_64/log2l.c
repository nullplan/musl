#include "libm.h"
#include "x87.h"

long double log2l(long double x)
{
	return x87_fyl2x(x, 1);
}
