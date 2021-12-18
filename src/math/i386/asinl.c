#include <math.h>

long double asinl(long double x)
{
	long double radicand = (1.0L - x) * (1.0L + x);
	long double denominator;
	__asm__("fsqrt" : "=t"(denominator) : "0"(radicand));
	__asm__("fpatan" : "=t"(x) : "0"(denominator), "u"(x) : "st(1)");
	return x;
}
