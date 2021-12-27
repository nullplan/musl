#include "libm.h"
#include "coreimpl.h"

float log10f(float x)
{
	return (float)log10_core(x);
}
