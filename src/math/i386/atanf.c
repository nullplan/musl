#include "libm.h"

float atanf(float x)
{
	uint32_t ix;
	GET_FLOAT_WORD(ix, x);
	if ((ix & 0x7fffffff) < 0x00800000)
	{
		FORCE_EVAL(x * x);
		return x;
	}
	__asm__("fpatan" : "=t"(x) : "0"(1.0L), "u"(x) : "st(1)");
	return x;
}
