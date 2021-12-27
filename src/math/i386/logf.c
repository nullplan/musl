#include "libm.h"
#include "coreimpl.h"

float logf(float x)
{
	return (float)log_core(x);
}
