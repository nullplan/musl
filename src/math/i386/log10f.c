#include "libm.h"

float log10f(float x)
{
	long double lg2;
	__asm__("fldlg2" : "=t"(lg2));
	__asm__("fyl2x" : "=t"(x) : "0"(x), "u"(lg2) : "st(1)");
	return x;
}
