#include "libm.h"

double atan2(double y, double x)
{
	uint32_t ix;
        long double res;
	__asm__("fpatan" : "=t"(res) : "0"(y), "u"(x) : "st(1)");
        x = (double)res;
	GET_HIGH_WORD(ix, x);
	if (unlikely((ix & 0x7fffffff) < 0x00100000))
	{
		volatile float f = x;	/* raise underflow for subnormal x */
	}
	return x;
}
