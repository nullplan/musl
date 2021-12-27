#include "libm.h"

double scalbln(double x, long int e)
{
	return scalbn(x, e);
}
