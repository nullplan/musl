#include "libm.h"
#include "coreimpl.h"

double log2(double x)
{
	return (double)log2_core(x);
}
