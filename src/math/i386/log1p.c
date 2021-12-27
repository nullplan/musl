#include "libm.h"

double log1p(double x)
{
	long double ln2;
	long double res;
	uint32_t ix;
	GET_HIGH_WORD(ix, x);
	ix &= 0x7fffffff;

	__asm__("fldln2" : "=t"(ln2));
	if (ix >= 0x3fd28f00) {
		__asm__("fyl2x" : "=t"(res) : "0"(x + 1), "u"(ln2) : "st(1)");
		return (double)res;
	}
	if (predict_false(ix < 0x00100000)) {
		/* subnormal x, return x with underflow */
		volatile float f = x;
		(void)f;
		return x;
	}

	__asm__("fyl2xp1" : "=t"(res) : "0"(x), "u"(ln2) : "st(1)");
	return (double)res;
}
