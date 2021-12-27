#include "libm.h"

double atan(double x)
{
	uint32_t ix;
	long double res;
	GET_HIGH_WORD(ix, x);
	ix &= 0x7fffffff;
	if (unlikely(ix < 0x00100000))
	{
		FORCE_EVAL(x * x);
		return x;
	}
	__asm__("fpatan" : "=t"(res) : "0"(1.0L), "u"(x) : "st(1)");
	return (double)res;
}
