#include "libm.h"
#include "coreimpl.h"

double remquo(double a, double b, int *quo)
{
	uint32_t ia, ib;
	GET_HIGH_WORD(ia, a);
	GET_HIGH_WORD(ib, b);
	return (double)remquo_core(a, b, quo, (ia ^ ib) >> 31);
}
