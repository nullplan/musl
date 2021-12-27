#include "libm.h"

#define X87_SW_C0 (1 << 8)
#define X87_SW_C1 (1 << 9)
#define X87_SW_C2 (1 << 10)
#define X87_SW_C3 (1 << 14)

static long double remquo_core(long double a, long double b, int *quo, int sgn)
{
	uint16_t sw;
	do
		__asm__("fprem1; fnstsw %w1" : "=t"(a), "=a"(sw) : "0"(a), "u"(b));
	while (sw & X87_SW_C2);

	int quobits = ((sw & X87_SW_C0) >> 6) | ((sw & X87_SW_C3) >> 13) | ((sw & X87_SW_C1) >> 9);
	if (sgn) quobits = -quobits;
	*quo = quobits;
	return a;
}

float remquof(float a, float b, int *quo)
{
	uint32_t ia, ib;
	GET_FLOAT_WORD(ia, a);
	GET_FLOAT_WORD(ib, b);
	return (float)remquo_core(a, b, quo, (ia ^ ib) >> 31);
}

double remquo(double a, double b, int *quo)
{
	uint32_t ia, ib;
	GET_HIGH_WORD(ia, a);
	GET_HIGH_WORD(ib, b);
	return (double)remquo_core(a, b, quo, (ia ^ ib) >> 31);
}

long double remquol(long double a, long double b, int *quo)
{
	union ldshape ia = {a}, ib = {b};
	return remquo_core(a, b, quo, (ia.i.se ^ ib.i.se) >> 15);
}
