#include "libm.h"

long double atan2l(long double y, long double x)
{
	__asm__("fpatan" : "=t"(x) : "0"(y), "u"(x) : "st(1)");
	return x;
}
