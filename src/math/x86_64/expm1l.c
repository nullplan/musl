#include "libm.h"
#include "x87.h"

long double expm1l(long double x)
{
	x *= x87_l2e();
	/* x*log2e <= -65, return -1 without underflow */
	if (x <= -65)
		return -1;
	if (x87_fabs(x) <= 1)
		return x87_f2xm1(x);
	return exp2l(x) - 1;
}
