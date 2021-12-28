#include <fenv.h>
#include <stdint.h>
#include "features.h"

static uint32_t rdmxcsr(void)
{
	uint32_t mxcsr;
	__asm__("stmxcsr %0" : "=m"(mxcsr));
	return mxcsr;
}

static void wrmxcsr(uint32_t mxcsr)
{
	__asm__("ldmxcsr %0" :: "m"(mxcsr) : "memory");
}

static uint16_t rdsw(void)
{
	uint16_t sw;
	__asm__("fnstsw %0" : "=am"(sw));
	return sw;
}

static uint16_t rdcw(void)
{
	uint16_t cw;
	__asm__("fnstcw %0" : "=m"(cw));
	return cw;
}

static void wrcw(uint16_t cw)
{
	__asm__("fldcw %0" :: "m"(cw) : "memory");
}

int feclearexcept(int ex)
{
	/* maintain exceptions in the sse mxcsr, clear x87 exceptions */
	ex &= 0x3f;
	uint16_t sw = rdsw();
	if (sw & ex)
		__asm__("fnclex" ::: "memory");
	uint32_t mxcsr = rdmxcsr() | (sw & 0x3f);
	if (mxcsr & ex)
		wrmxcsr(mxcsr & ~ex);
	return 0;
}

int feraiseexcept(int ex)
{
	ex &= 0x3f;
	wrmxcsr(rdmxcsr() | ex);
	return 0;
}

hidden int __fesetround(int rm)
{
	wrcw((rdcw() & 0xf3ff) | rm);
	wrmxcsr((rdmxcsr() & 0xffff9fff) | (rm << 3));
	return 0;
}

int fegetround(void)
{
	return (rdmxcsr() >> 3) & 0xc00;
}

int fegetenv(fenv_t *fe)
{
	__asm__("fnstenv %0" : "=m"(*fe));
	fe->__mxcsr = rdmxcsr();
	return 0;
}

int fesetenv(const fenv_t *fe)
{
	if (fe == FE_DFL_ENV) {
		static const fenv_t dflenv = {.__control_word = 0x37f, .__tags = 0xffff, .__mxcsr = 0x1f80};
		fe = &dflenv;
	}
	__asm__("fldenv %0" :: "m"(*fe) : "memory");
	wrmxcsr(fe->__mxcsr);
	return 0;
}

int fetestexcept(int ex)
{
	ex &= 0x3f;
	return (rdmxcsr() | rdsw()) & ex;
}
