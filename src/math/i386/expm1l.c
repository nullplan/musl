#include "libm.h"

long double expm1l(long double x)
{
	long double l2e;
	__asm__("fldl2e" : "=t"(l2e));
	x *= l2e;
	if (x < -65)
		return -1;
	long double absx;
	__asm__("fabs" : "=t"(absx) : "0"(x));
	if (absx <= 1) {
		__asm__("f2xm1" : "=t"(x) : "0"(x));
		return x;
	}
	return exp2l(x) - 1;
}
