#include "libm.h"

double log1p(double x)
{
	long double ln2;
	uint32_t ix;
	GET_HIGH_WORD(ix, x);
	ix &= 0x7fffffff;

	__asm__("fldln2" : "=t"(ln2));
	if (ix >= 0x3fd28f00) {
		__asm__("fyl2x" : "=t"(x) : "0"(x + 1), "u"(ln2) : "st(1)");
		return x;
	}
	if (unlikely(ix < 0x00100000)) {
		/* subnormal x, return x with underflow */
		volatile float f = x;
		return x;
	}

	__asm__("fyl2xp1" : "=t"(x) : "0"(x), "u"(ln2) : "st(1)");
	return x;
}
