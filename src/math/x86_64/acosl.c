#include "libm.h"
#include "x87.h"

long double acosl(long double x)
{
	return x87_fpatan(x, x87_fabs(x87_fsqrt((1+x)*(1-x))));
}
