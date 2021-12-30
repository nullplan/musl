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

static inline long double x87_frndint_rm(long double x, int rm)
{
	uint16_t cw_old, cw_new;
	__asm__("fstcw %0" : "=m"(cw_old));
	cw_new = (cw_old & 0xff00) | rm;
	__asm__("fldcw %0" :: "m"(cw_new) : "memory");
	__asm__("frndint" : "+t"(x));
	__asm__("fldcw %0" :: "m"(cw_old) : "memory");
	return x;
}
#endif
