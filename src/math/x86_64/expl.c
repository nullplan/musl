#include "libm.h"
#include "x87.h"


/* exp(x) = 2^hi + 2^hi (2^lo - 1)
 * where hi+lo = log2e*x with 128bit precision
 * exact log2e*x calculation depends on nearest rounding mode
 * using the exact multiplication method of Dekker and Veltkamp
 */

long double expl(long double x)
{
	/* interesting case: 0x1p-32 <= |x| < 16384
	 * check if (exponent|0x8000) is in [0xbfff-32, 0xbfff+13]
	 */
	union ldshape ix = {x};
	if ((ix.i.se | 0x8000) - 0xbfdfu > 45u) {
		/* if |x|>=0x1p14 or nan return 2^trunc(x) */
		if ((ix.i.se | 0x8000) >= 0xbfdf)
			return x87_fscale(1, x);

		/* if |x|<0x1p-32 return 1+x */
		return x+1;
	}
	long double hi = x87_l2e() * x;
	long double two_raised_hi = exp2l(hi);
	/* if 2^hi == in return 2^hi */
	ix.f = two_raised_hi;
	if (ix.i.se == 0x7fff) return two_raised_hi;

	long double cx = 0x1.00000001p32 * x;
	long double xh = x - cx + cx;
	long double xl = x - xh;
	/* yh = log2e_hi - c*log2e_hi + c*log2e_hi */
	long double yh = 0x1.71547652p0;
	long double lo = hi - xh*yh + xl*yh;
	/* yl = log2e_hi - yh */
	long double yl = 0x1.705fc2fp-33;
	lo += xh*yl + xl*yl;
	long double log2e_lo = -0x1.05e004be5b8b05dcp-65;
	lo += log2e_lo * x;
	return two_raised_hi + two_raised_hi * x87_f2xm1(lo);
}
