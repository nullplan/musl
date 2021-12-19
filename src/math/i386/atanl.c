#include "libm.h"

long double atanl(long double x)
{
	__asm__("fpatan" : "=t"(x) : "0"(1.0L), "u"(x) : "st(1)");
	return x;
}
