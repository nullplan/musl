#include "libm.h"

double hypot(double x, double y)
{
	uint32_t hx, lx, hy, ly;
	EXTRACT_WORDS(hx, lx, x);
	EXTRACT_WORDS(hy, ly, y);
	if (predict_true((hx & hy & 0x7ff00000) != 0x7ff00000)) {
		/* x == 0 -> return |y| */
		if (2 * hx + lx == 0) {
			__asm__("fabs" : "+t"(y));
			return y;
		}
		/* y == 0 -> return |x| */
		if (2 * hy + ly == 0) {
			__asm__("fabs" : "+t"(x));
			return x;
		}
		/* Else go the long way around. */
		long double res;
		__asm__("fsqrt" : "=t"(res) : "0"(x * x + y * y));
		return (double)res;
	}

	/* both inputs are inf or nan */
	/* if x is inf, return |x| */
	if (!((hx & 0x000fffff) | lx)) {
		__asm__("fabs" : "+t"(x));
		return x;
	}
	/* So x is nan. If y is inf, return |y| */
	if (!((hy & 0x000fffff) | ly))
		__asm__("fabs" : "+t"(y));
	/* Else return y (so nan) */
	return y;
}
