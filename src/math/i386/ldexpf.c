#include "libm.h"

float ldexpf(float x, int e)
{
	return scalbnf(x, e);
}
