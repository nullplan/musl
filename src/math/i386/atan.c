#include "libm.h"
#include "coreimpl.h"

double atan(double x)
{
	uint32_t ix;
	GET_HIGH_WORD(ix, x);
	ix &= 0x7fffffff;
	if (predict_false(ix < 0x00100000)) {
		FORCE_EVAL(x * x);
		return x;
	}
	return (double)atan_core(x);
}
