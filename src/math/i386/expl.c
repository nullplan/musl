#include "libm.h"

/* exp(x) = 2^hi + 2^hi (2^lo - 1)
 * where hi+lo = log2e*x with 128bit precision
 * exact log2e*x calculation depends on nearest rounding mode
 * using the exact multiplication method of Dekker and Veltkamp
 */

long double expl(long double x)
{
	union ldshape u = {x};
	if ((u.i.se | 0x8000) - 0xbfdfu > 45) {
		if ((u.i.se | 0x8000) - 0xbfdfu < 0x8000u) {
			/* if |x|>=0x1p14 or nan return 2^trunc(x) */
			__asm__("fscale" : "=t"(x) : "0"(1.0L), "u"(x));
		} else {
			/* if |x| < 0x1p-32 return 1+x */
			x += 1;
		}
		return x;
	}
	/* else it gets complicated. */
	long double l2e;
	__asm__("fldl2e" : "=t"(l2e));

	long double hi = l2e * x;
	long double two_raised_hi = exp2l(hi);

	/* if 2^hi == inf return 2^hi */
	u.f = two_raised_hi;
	if (u.i.se == 0x7fff)
		return two_raised_hi;

	long double cx = 0x1.00000001p32 * x;
	long double xh = x - cx + cx;
	long double xl = x - xh;
	long double yh = 0x1.71547652p0;
	long double yl = 0x1.705fc2fp-33;
	long double lo = hi - xh * yh + xl * yh;
	long double log2e_lo = -0x1.05e004be5b8b05dcp-65;
	lo = lo + xh * yl + xl * yl;
	__asm__("f2xm1" : "=t"(x) : "0"(lo + log2e_lo * x));
	return x * two_raised_hi + two_raised_hi;
}
