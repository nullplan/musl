#include "libm.h"
#include "x87.h"

long double exp2l(long double x)
{
	union ldshape ix = {x};
	ix.i.se &= 0x7fff;
	if (ix.i.se >= 0x3fff+13 && ix.i.se < 0x3fff+15) {
		/* 8192 <= |x| < 32768 */
		uint32_t ifx;
		GET_FLOAT_WORD(ifx, (float)x);
		/* x >= -16382 && x has any mantissa bit below the 13th or 14th set. */
		if (ifx >= 0xc67ff800 && x - 0x1.0p63 + 0x1.0p63 != x)
			FORCE_EVAL((float)(0x1p-149/x));    /* raise underflow */
		long double rx = x87_frndint(x);
		return x87_fscale(x87_f2xm1(x - rx) + 1, rx);
	} else {
		if (ix.i.se >= 0x3fff+15 || ix.i.se < 0x3fff-64)
			return x87_fscale(1, x);
		ix.f = 1.0;
		int32_t rx = x;
		ix.i.se = rx + 0x3fff;
		return (x87_f2xm1(x - rx) + 1) * ix.f;
	}
}
