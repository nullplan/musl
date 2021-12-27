#include "libm.h"
#include "coreimpl.h"

double asin(double x)
{
	uint32_t ix;
	GET_HIGH_WORD(ix, x);
	if (predict_false((ix & 0x7fffffff) < 0x00100000))    /* subnormal x, return x with underflow */
	{
		volatile float f = x;
		return x;
	}
	return (double)asin_core(x);
}
