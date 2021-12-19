#include "libm.h"

static long double rndint(long double x, uint16_t rm)
{
	uint16_t cw_old, cw_new;
	__asm__("fstcw %0" : "=m"(cw_old));
	cw_new = (cw_old & 0xff00) | rm;
	__asm__("fldcw %0" :: "m"(cw_new) : "memory");
	__asm__("frndint" : "=t"(x) : "0"(x));
	__asm__("fldcw %0" :: "m"(cw_old) : "memory");
	return x;
}

float floorf(float x)
{
	return rndint(x, 7);
}

double floor(double x)
{
	return rndint(x, 7);
}

long double floorl(long double x)
{
	return rndint(x, 7);
}

float ceilf(float x)
{
	return rndint(x, 11);
}

double ceil(double x)
{
	return rndint(x, 11);
}

long double ceill(long double x)
{
	return rndint(x, 11);
}

float truncf(float x)
{
	return rndint(x, 15);
}

double trunc(double x)
{
	return rndint(x, 15);
}

long double truncl(long double x)
{
	return rndint(x, 15);
}
