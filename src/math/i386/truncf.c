#include "libm.h"
#include "coreimpl.h"
float truncf(float x)
{
	return (float)rndint(x, 15);
}
