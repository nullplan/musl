#include "libm.h"
#include "coreimpl.h"

float atan2f(float y, float x)
{
	uint32_t ix;
	x = (float)atan2_core(y, x);
	GET_FLOAT_WORD(ix, x);
	if (predict_false((ix & 0x7fffffff) < 0x00800000))
		FORCE_EVAL(x * x);
	return x;
}
