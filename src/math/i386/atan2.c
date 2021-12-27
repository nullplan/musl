#include "libm.h"
#include "coreimpl.h"

double atan2(double y, double x)
{
	uint32_t ix;
	x = (double)atan2_core(y, x);
	GET_HIGH_WORD(ix, x);
	if (predict_false((ix & 0x7fffffff) < 0x00100000))
	{
		volatile float f = x;	/* raise underflow for subnormal x */
		(void)f;
	}
	return x;
}
