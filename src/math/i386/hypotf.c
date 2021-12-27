#include "libm.h"

float hypotf(float x, float y)
{
	uint32_t ix, iy;
	GET_FLOAT_WORD(ix, x);
	GET_FLOAT_WORD(iy, y);
	if (likely((ix & iy & 0x7f800000) != 0x7f800000)) {
		if (2 * ix == 0) {
			__asm__("fabs" : "+t"(y));
			return y;
		}
		if (2 * iy == 0) {
			__asm__("fabs" : "+t"(x));
			return x;
		}
                long double res;
		__asm__("fsqrt" : "=t"(res) : "0"(y * y + x * x));
		return (float)res;
	}

	if (!(ix & 0x007fffff)) {
		__asm__("fabs" : "+t"(x));
		return x;
	}

	if (!(iy & 0x007fffff))
		__asm__("fabs" : "+t"(y));
	return y;
}
