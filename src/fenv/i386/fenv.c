#include <fenv.h>
#include <stdint.h>
#include <stddef.h>
#include "features.h"

extern hidden size_t __hwcap;
#define HWCAP_SSE 0x02000000

int feclearexcept(int ex)
{
	uint16_t sw;
	__asm__("fnstsw %w0" : "=a"(sw));
	ex &= 0x3f;
	/* consider sse fenv as well if the cpu has XMM capability */
	if (__hwcap & HWCAP_SSE) {
		/* maintain exceptions in the SSE MXCSR, clear x87 exceptions */
		if (sw & ex)
			__asm__("fnclex" ::: "memory");

		uint32_t mxcsr;
		__asm__("stmxcsr %0" : "=m"(mxcsr));
		sw &= 0x3f;
		mxcsr |= sw;
		if (mxcsr & ex) {
			mxcsr &= ~ex;
			__asm__("ldmxcsr %0" :: "m"(mxcsr) : "memory");
		}
	} else {
		/* only do the expensive x87 fenv load/store when needed */
		if (!(sw & ex))
			return 0;
		sw &= ~ex;
		if (sw & 0x3f) {
			fenv_t env;
			__asm__("fnstenv %0" : "=m"(env));
			env.__status_word = (env.__status_word & 0xff00) | (sw & 0xff);
			__asm__("fldenv %0" :: "m"(env) : "memory");
		} else
			__asm__("fnclex" ::: "memory");
	}
	return 0;
}

int feraiseexcept(int ex)
{
	/* XXX: Why not test for SSE? */
	fenv_t env;
	ex &= 0x3f;
	__asm__("fnstenv %0" : "=m"(env));
	env.__status_word |= ex;
	__asm__("fldenv %0" :: "m"(env) : "memory");
	return 0;
}

hidden int __fesetround(int rm)
{
	uint16_t cw;
	__asm__("fnstcw %0" : "=m"(cw));
	cw = (cw & 0xf3ff) | rm;
	__asm__("fldcw %0" :: "m"(cw) : "memory");
	if (__hwcap & HWCAP_SSE) {
		uint32_t mxcsr;
		__asm__("stmxcsr %0" : "=m"(mxcsr));
		mxcsr = (mxcsr & 0xffff9fff) | (rm << 3);
		__asm__("ldmxcsr %0" :: "m"(mxcsr) : "memory");
	}
	return 0;
}

int fegetround(void) {
	uint16_t cw;
	__asm__("fnstcw %0" : "=m"(cw));
	return cw & 0xc00;
}

int fegetenv(fenv_t *fe)
{
	__asm__("fnstenv %0" : "=m"(*fe));
	if (__hwcap & HWCAP_SSE)
	{
		uint32_t mxcsr;
		__asm__("stmxcsr %0" : "=m"(mxcsr));
		fe->__status_word |= mxcsr & 0x3f;
	}
	return 0;
}

int fesetenv(const fenv_t *fe)
{
	uint16_t sw;
	if (fe == FE_DFL_ENV)
	{
		static const fenv_t defenv = {.__control_word = 0x37f, .__tags = 0xffff};
		sw = 0;
		__asm__("fldenv %0" :: "m"(defenv) : "memory");
	} else {
		sw = fe->__status_word;
		__asm__("fldenv %0" :: "m"(*fe) : "memory");
	}

	if (__hwcap & HWCAP_SSE) {
		uint32_t mxcsr;
		/* mxcsr := same rounding mode, cleared exceptions, default mask */
		mxcsr = ((sw & 0xc00) << 3) | 0x1f80;
		__asm__("ldmxcsr %0" :: "m"(mxcsr) : "memory");
	}
	return 0;
}

int fetestexcept(int ex)
{
	uint16_t sw;
	ex &= 0x3f;
	__asm__("fnstsw %0" : "=a"(sw));
	if (__hwcap & HWCAP_SSE) {
		uint32_t mxcsr;
		__asm__("stmxcsr %0" : "=m"(mxcsr));
		sw |= mxcsr;
	}
	return sw & ex;
}
