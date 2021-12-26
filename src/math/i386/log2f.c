#include "libm.h"

float log2f(float x)
{
	long double t;
	__asm__("fyl2x" : "=t"(t) : "0"(x), "u"(1.0) : "st(1)");
	return t;
}
