#include "libm.h"
#include "x87.h"

long double logl(long double x)
{
	return x87_fyl2x(x, x87_ln2());
}
