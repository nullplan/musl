#include "libm.h"

double scalbn(double x, int e)
{
	if (e + 0x3ffeu >= 0x7ffd)
	{
		e >>= 31;
		e ^= 0xfff;
	}

	union ldshape mult;
	mult.i.se = e + 0x3fff;
	mult.i.m = (1ull << 63);
	return (double)(x * mult.f);
}
