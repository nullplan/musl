#include "libm.h"
#include "x87.h"

long double asinl(long double x)
{
	return x87_fpatan(x87_fsqrt((1+x)*(1-x)), x);
}
