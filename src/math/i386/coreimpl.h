#ifndef MATH_I386_COREIMPL_H
#define MATH_I386_COREIMPL_H

#include <stdint.h>

static inline long double x87_fsqrt(long double x)
{
	__asm__("fsqrt" : "+t"(x));
	return x;
}

static inline long double x87_fabs(long double x)
{
	__asm__("fabs" : "+t"(x));
	return x;
}

static inline long double x87_fpatan(long double y, long double x)
{
	__asm__("fpatan" : "=t"(x) : "0"(y), "u"(x) : "st(1)");
	return x;
}

static inline long double x87_fyl2x(long double x, long double y)
{
	__asm__("fyl2x" : "=t"(x) : "0"(x), "u"(y) : "st(1)");
	return x;
}

static inline long double x87_ln2(void)
{
	long double ln2;
	__asm__("fldln2" : "=t"(ln2));
	return ln2;
}

static inline long double x87_lg2(void)
{
	long double lg2;
	__asm__("fldlg2" : "=t"(lg2));
	return lg2;
}

static inline long double acos_core(long double x)
{
	long double radicand = (1.0L - x) * (1.0L + x);
	return x87_fpatan(x, x87_fabs(x87_fsqrt(radicand)));
}

static inline long double asin_core(long double x)
{
	long double radicand = (1.0L - x) * (1.0L + x);
	return x87_fpatan(x87_fsqrt(radicand), x);
}

static inline long double atan_core(long double x)
{
	return x87_fpatan(1.0, x);
}

static inline long double atan2_core(long double y, long double x)
{
	return x87_fpatan(y, x);
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
	return x87_fsqrt(x*x + y*y);
}

static inline long double log2_core(long double x)
{
	return x87_fyl2x(x, 1.0);
}

static inline long double log_core(long double x)
{
	return x87_fyl2x(x, x87_ln2());
}

static inline long double log10_core(long double x)
{
	return x87_fyl2x(x, x87_lg2());
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
