#include "libm.h"
#include "coreimpl.h"

float remquof(float a, float b, int *quo)
{
	uint32_t ia, ib;
	GET_FLOAT_WORD(ia, a);
	GET_FLOAT_WORD(ib, b);
	return (float)remquo_core(a, b, quo, (ia ^ ib) >> 31);
}
