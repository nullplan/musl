#include "libm.h"

double asin(double x)
{
	uint32_t ix;
        GET_HIGH_WORD(ix, x);
	if (predict_false((ix & 0x7fffffff) < 0x00100000))    /* subnormal x, return x with underflow */
	{
		volatile float f = x;
		return x;
	}
	long double radicand = (1.0L - x) * (1.0L + x);
	long double denominator;
        long double res;
	__asm__("fsqrt" : "=t"(denominator) : "0"(radicand));
	__asm__("fpatan" : "=t"(res) : "0"(denominator), "u"(x) : "st(1)");
	return (double)res;
}
