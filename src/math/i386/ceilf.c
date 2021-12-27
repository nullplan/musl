#include "libm.h"
#include "coreimpl.h"

float ceilf(float x)
{
	return (float)rndint(x, 11);
}
