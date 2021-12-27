#ifndef MATH_I386_COREIMPL_H
#define MATH_I386_COREIMPL_H

#include <stdint.h>

/* use acos(x) = atan2(fabs(sqrt((1-x)*(1+x))), x) */
static inline long double acos_core(long double x)
{
	long double radicand = (1.0L - x) * (1.0L + x);
	long double numerator;
	/* fabs to fix sign of zero (matters in downward rounding mode) */
	__asm__("fsqrt; fabs" : "=t"(numerator) : "0"(radicand));
	__asm__("fpatan" : "=t"(x) : "0"(x), "u"(numerator) : "st(1)");
	return x;
}

/* use asin(x) = atan2(x, sqrt((1-x)*(1+x))) */
static inline long double asin_core(long double x)
{
	long double radicand = (1.0L - x) * (1.0L + x);
	long double denominator;
	__asm__("fsqrt" : "=t"(denominator) : "0"(radicand));
	__asm__("fpatan" : "=t"(x) : "0"(denominator), "u"(x) : "st(1)");
	return x;
}

static inline long double atan_core(long double x)
{
	__asm__("fpatan" : "=t"(x) : "0"(1.0L), "u"(x) : "st(1)");
	return x;
}

static inline long double atan2_core(long double y, long double x)
{
	__asm__("fpatan" : "=t"(x) : "0"(y), "u"(x) : "st(1)");
	return x;
}

/* the core of ceil, floor, and trunc */
static inline long double rndint(long double x, uint16_t rm)
{
	uint16_t cw_old, cw_new;
	__asm__("fstcw %0" : "=m"(cw_old));
	cw_new = (cw_old & 0xff00) | rm;
	__asm__("fldcw %0" :: "m"(cw_new) : "memory");
	__asm__("frndint" : "=t"(x) : "0"(x));
	__asm__("fldcw %0" :: "m"(cw_old) : "memory");
	return x;
}

static inline long double hypot_core(long double x, long double y)
{
	__asm__("fsqrt" : "=t"(x) : "0"(x*x + y*y));
	return x;
}

static inline long double log2_core(long double x)
{
	__asm__("fyl2x" : "=t"(x) : "0"(x), "u"(1.0) : "st(1)");
	return x;
}

static inline long double log_core(long double x)
{
	long double ln2;
	__asm__("fldln2" : "=t"(ln2));
	__asm__("fyl2x" : "=t"(x) : "0"(x), "u"(ln2) : "st(1)");
	return x;
}

static inline long double log10_core(long double x)
{
	long double lg2;
	__asm__("fldlg2" : "=t"(lg2));
	__asm__("fyl2x" : "=t"(x) : "0"(x), "u"(lg2) : "st(1)");
	return x;
}

static inline long lrint_core(long double x)
{
	long r;
	__asm__ ("fistpl %0" : "=m"(r) : "t"(x) : "st");
	return r;
}

#define X87_SW_C0 (1 << 8)
#define X87_SW_C1 (1 << 9)
#define X87_SW_C2 (1 << 10)
#define X87_SW_C3 (1 << 14)

static inline long double remquo_core(long double a, long double b, int *quo, int sgn)
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

#endif
