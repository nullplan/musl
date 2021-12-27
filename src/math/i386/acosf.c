#include <math.h>

/* use acos(x) = atan2(fabs(sqrt((1-x)*(1+x))), x) */
float acosf(float x)
{
	long double radicand = (1.0L - x) * (1.0L + x);
	long double numerator;
        long double res;
	/* fabs to fix sign of zero (matters in downward rounding mode) */
	__asm__("fsqrt; fabs" : "=t"(numerator) : "0"(radicand));
	__asm__("fpatan" : "=t"(res) : "0"(x), "u"(numerator) : "st(1)");
	return (float)res;
}
