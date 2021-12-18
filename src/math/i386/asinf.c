#include "libm.h"

float asinf(float x)
{
	uint32_t ix;
	GET_FLOAT_WORD(ix, x);
	if (ix+ix < 0x01000000)
	{
		FORCE_EVAL(x * x);
		return x;
	}
	long double radicand = (1.0L - x) * (1.0L + x);
	long double denom;
	__asm__("fsqrt" : "=t"(denom) : "0"(radicand));
	__asm__("fpatan" : "=t"(x) : "0"(denom), "u"(x) : "st(1)");
	return x;
}
