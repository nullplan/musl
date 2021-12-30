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

static inline long double x87_fpatan(long double y, long double x)
{
	__asm__("fpatan" : "=t"(x) : "0"(y), "u"(x) : "st(1)");
	return x;
}
#endif
