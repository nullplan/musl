#ifndef X87_H
#define X87_H

static inline long double x87_fabs(long double x)
{
	__asm__("fabs" : "+t"(x));
	return x;
}

static inline long double x87_fsqrt(long double x)
{
	__asm__("fsqrt" : "+t"(x));
	return x;
}

static inline long double x87_fpatan(long double x, long double y)
{
	__asm__("fpatan" : "=t"(x) : "0"(x), "u"(y) : "st(1)");
	return x;
}

static inline long double x87_frndint(long double x)
{
	__asm__("frndint" : "+t"(x));
	return x;
}

static inline long double x87_frndint_rm(long double x, int rm)
{
	uint16_t cw_old, cw_new;
	__asm__("fstcw %0" : "=m"(cw_old));
	cw_new = (cw_old & 0xff00) | rm;
	__asm__("fldcw %0" :: "m"(cw_new) : "memory");
	x = x87_frndint(x);
	__asm__("fldcw %0" :: "m"(cw_old) : "memory");
	return x;
}

static inline long double x87_f2xm1(long double x)
{
	__asm__("f2xm1" : "+t"(x));
	return x;
}

static inline long double x87_fscale(long double x, long double scale)
{
	__asm__("fscale" : "+t"(x) : "u"(scale));
	return x;
}

static inline long double x87_l2e(void)
{
	long double r;
	__asm__("fldl2e" : "=t"(r));
	return r;
}

static inline long double x87_lg2(void)
{
	long double r;
	__asm__("fldlg2" : "=t"(r));
	return r;
}

static inline long double x87_fyl2x(long double x, long double y)
{
	__asm__("fyl2x" : "=t"(x) : "0"(x), "u"(y) : "st(1)");
	return x;
}
#endif
