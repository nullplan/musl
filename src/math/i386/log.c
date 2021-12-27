#include "libm.h"
#include "coreimpl.h"

double log(double x)
{
	return (double)log_core(x);
}
