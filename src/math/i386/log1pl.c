#include "libm.h"

long double log1pl(long double x)
{
	long double ln2;
	__asm__("fldln2" : "=t"(ln2));

	union ldshape ix = {x};
	ix.i.se &= 0x7fffffff;
	if (ix.i.se > 0x3ffd || (ix.i.se == 0x3ffd && (ix.i.m >> 48) > 0x9400))
	{
		__asm__("fyl2x" : "=t"(x) : "0"(x + 1), "u"(ln2) : "st(1)");
		return x;
	}

	__asm__("fyl2xp1" : "=t"(x) : "0"(x), "u"(ln2) : "st(1)");
	return x;
}
