#include "libm.h"

double log2(double x)
{
	long double t;
	__asm__("fyl2x" : "=t"(t) : "0"(x), "u"(1.0) : "st(1)");
	return t;
}
