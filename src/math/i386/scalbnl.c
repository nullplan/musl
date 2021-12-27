#include "libm.h"

long double scalbnl(long double x, int e)
{
	if (e + 0x3ffeu >= 0x7ffd)
	{
		__asm__("fscale" : "=t"(x) : "0"(x), "u"((long double)e));
		return x;
	}

	union ldshape mult;
	mult.i.se = e + 0x3fff;
	mult.i.m = 1ull << 63;
	return x * mult.f;
}
