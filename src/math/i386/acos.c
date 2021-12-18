#include <math.h>

/* use acos(x) = atan2(fabs(sqrt((1-x)*(1+x))), x) */
double acos(double x)
{
	long double radicand = (1.0L - x) * (1.0L + x);
	long double numerator;
	/* fabs to fix sign of zero (matters in downward rounding mode) */
	__asm__("fsqrt; fabs" : "=t"(numerator) : "0"(radicand));
	__asm__("fpatan" : "=t"(x) : "0"(x), "u"(numerator) : "st(1)");
	return x;
}
