#include "libm.h"

long double exp2l(long double x)
{
	union ldshape u = {x};
	uint32_t r;
	u.i.se &= 0x7fff;
	if (u.i.se >= 0x3fff + 13 && u.i.se < 0x3fff + 15) {
		if (x <= -16382 && x - 0x1p63 + 0x1p63 != x) {
			volatile float f = 0x1p-149; // raise underflow
			(void)f;
		}
		long double rint;
		long double mant;
		__asm__("frndint" : "=t"(rint) : "0"(x));
		__asm__("f2xm1" : "=t"(mant) : "0"(x - rint));
		__asm__("fscale" : "=t"(x) : "0"(mant + 1), "u"(rint));
		return x;
	}
	if (u.i.se >= 0x3fff + 15)
		u.i.se = 0;
	if (u.i.se < 0x3fff - 64)
	{
		__asm__("fscale" : "=t"(x) : "0"(1.0L), "u"(x));
		return x;
	}
	u.i.m = 0;
	r = x;
	u.i.se = r + 0x3fff;
	__asm__("f2xm1" : "=t"(x) : "0"(x - r));
	return (x + 1) * u.f;
}
