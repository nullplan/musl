#include "libm.h"

long double log2l(long double x)
{
	__asm__("fyl2x" : "=t"(x) : "0"(x), "u"(1.0) : "st(1)");
	return x;
}
