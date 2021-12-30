#include "libm.h"
#include "x87.h"

long double log1pl(long double x)
{
	union ldshape ix = {x};
	uint32_t hi = (ix.i.se & 0x7fff) << 16 | ix.i.m >> 48;
	if (hi >= 0x3ffd9400)
		return x87_fyl2x(1+x, x87_ln2());
	return x87_fyl2xp1(x, x87_ln2());
}
