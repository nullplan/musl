#include "libm.h"
#include "coreimpl.h"

float hypotf(float x, float y)
{
	uint32_t ix, iy;
	GET_FLOAT_WORD(ix, x);
	GET_FLOAT_WORD(iy, y);
	if (predict_true((ix & iy & 0x7f800000) != 0x7f800000)) {
		if (2 * ix == 0) {
			__asm__("fabs" : "+t"(y));
			return y;
		}
		if (2 * iy == 0) {
			__asm__("fabs" : "+t"(x));
			return x;
		}
		return (float)hypot_core(x, y);
	}

	if (!(ix & 0x007fffff)) {
		__asm__("fabs" : "+t"(x));
		return x;
	}

	if (!(iy & 0x007fffff))
		__asm__("fabs" : "+t"(y));
	return y;
}
