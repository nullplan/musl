#include "libm.h"
#include "x87.h"

long double atanl(long double x)
{
	return x87_fpatan(1, x);
}
