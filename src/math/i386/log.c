#include "libm.h"

double log(double x)
{
	long double ln2;
	long double res;
	__asm__("fldln2" : "=t"(ln2));
	__asm__("fyl2x" : "=t"(res) : "0"(x), "u"(ln2) : "st(1)");
	return (double)res;
}
