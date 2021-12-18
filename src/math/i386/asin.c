#include "libm.h"

double asin(double x)
{
	uint32_t ix;
        GET_HIGH_WORD(ix, x);
	if (ix + ix < 0x00200000)    /* subnormal x, return x with underflow */
	{
		FORCE_EVAL(x * x);
		return x;
	}
	long double radicand = (1.0L - x) * (1.0L + x);
	long double denominator;
	__asm__("fsqrt" : "=t"(denominator) : "0"(radicand));
	__asm__("fpatan" : "=t"(x) : "0"(denominator), "u"(x) : "st(1)");
	return x;
}
