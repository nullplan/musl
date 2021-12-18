#include <math.h>

/* use acos(x) = atan2(fabs(sqrt((1-x)*(1+x))), x) */
double acos(double x)
{
	long double lx = x;
	long double one;
	__asm__("fld1" : "=t"(one));
	long double radicand = (one - lx) * (one + lx);
	long double numerator;
	/* fabs to fix sign of zero (matters in downward rounding mode) */
	__asm__("fsqrt; fabs" : "=t"(numerator) : "0"(radicand));
	__asm__("fpatan" : "=t"(lx) : "0"(lx), "u"(numerator) : "st(1)");
	return lx;
}
