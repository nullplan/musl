#include "libm.h"

double log10(double x)
{
	long double lg2;
        long double res;
	__asm__("fldlg2" : "=t"(lg2));
	__asm__("fyl2x" : "=t"(res) : "0"(x), "u"(lg2) : "st(1)");
	return (double)res;
}
