#include "libm.h"
#include "coreimpl.h"

long double expm1l(long double x)
{
	x *= x87_l2e();
	if (x < -65)
		return -1;
	if (x87_fabs(x) <= 1) {
		__asm__("f2xm1" : "=t"(x) : "0"(x));
		return x;
	}
	return exp2l(x) - 1;
}
