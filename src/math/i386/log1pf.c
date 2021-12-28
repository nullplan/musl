#include "libm.h"

float log1pf(float x)
{
	uint32_t ix;
	long double res;
	GET_FLOAT_WORD(ix, x);
	ix &= 0x7fffffff;

	long double ln2;
	__asm__("fldln2" : "=t"(ln2));
	if (ix > 0x3e940000) {
		__asm__("fyl2x" : "=t"(res) : "0"(x + 1), "u"(ln2) : "st(1)");
		return (float)res;
	}
	if (predict_false(ix < 0x00800000))
	{
		/* subnormal x, return x with underflow */
		FORCE_EVAL(x*x);
		return x;
	}

	__asm__("fyl2xp1" : "=t"(res) : "0"(x), "u"(ln2) : "st(1)");
	return (float)res;
}
