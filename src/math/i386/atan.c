#include "libm.h"

double atan(double x)
{
	uint32_t ix;
	GET_HIGH_WORD(ix, x);
	ix &= 0x7fffffff;
	if (unlikely(ix < 0x00100000))
	{
		FORCE_EVAL(x * x);
		return x;
	}
	__asm__("fpatan" : "=t"(x) : "0"(1.0L), "u"(x) : "st(1)");
	return x;
}
