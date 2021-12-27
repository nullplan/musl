#include "libm.h"
#include "coreimpl.h"

double log10(double x)
{
	return (double)log10_core(x);
}
