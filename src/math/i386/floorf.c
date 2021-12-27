#include "libm.h"
#include "coreimpl.h"
float floorf(float x)
{
	return (float)rndint(x, 7);
}
