#include "libm.h"
#include "coreimpl.h"

float atanf(float x)
{
	uint32_t ix;
	GET_FLOAT_WORD(ix, x);
	if (predict_false((ix & 0x7fffffff) < 0x00800000))
	{
		FORCE_EVAL(x * x);
		return x;
	}
	return (float)atan_core(x);
}
