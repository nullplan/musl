#include "libm.h"

float atan2f(float y, float x)
{
	uint32_t ix;
        long double res;
	__asm__("fpatan" : "=t"(res) : "0"(y), "u"(x) : "st(1)");
        x = (float)res;
	GET_FLOAT_WORD(ix, x);
	if ((ix & 0x7fffffff) < 0x00800000)
		FORCE_EVAL(x * x);
	return x;
}
