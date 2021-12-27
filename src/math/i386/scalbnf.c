#include "libm.h"

float ldexpf(float x, int e)
{
	return scalbnf(x, e);
}

float scalblnf(float x, long e)
{
	return scalbnf(x, e);
}

float scalbnf(float x, int e)
{
	if (e + 0x3feu >= 0x7fd)
	{
		e >>= 1;
		e ^= 0x1ff;
	}
	double mult;
	INSERT_WORDS(mult, (e + 0x3ff) << 20, 0);
	return (float)(x * mult);
}

