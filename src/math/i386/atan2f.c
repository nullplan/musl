#include "libm.h"

float atan2f(float y, float x)
{
	uint32_t ix;
	__asm__("fpatan" : "=t"(x) : "0"(y), "u"(x) : "st(1)");
	GET_HIGH_WORD(ix, x);
	if ((ix & 0x7fffffff) < 0x00800000)
		FORCE_EVAL(x * x);
	return x;
}
