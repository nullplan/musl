#include "libm.h"
#include "coreimpl.h"

float log2f(float x)
{
	return (float)log2_core(x);
}
