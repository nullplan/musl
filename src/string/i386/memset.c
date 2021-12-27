#include <string.h>
#include <stdint.h>

void *memset(void * const dst, int c, size_t len)
{
	char *cdst = dst;
	uint32_t wc = c * 0x01010101;
	typedef uint16_t __attribute__((may_alias)) halfword_t;
	typedef uint32_t __attribute__((may_alias)) word_t;
	if (len < 62) {
		if (!len) return dst;
		cdst[0] = cdst[len - 1] = c;
		if (len <= 2) return dst;
		*(halfword_t*)(cdst + 1) = *(halfword_t*)(cdst + len -1-2) = wc;
		if (len <= 6) return dst;
		*(word_t*)(cdst +1+2) = *(word_t*)(cdst + len -1-2-4) = wc;
		if (len <= 14) return dst;
		*(word_t*)(cdst + 1+2+4) = *(word_t*)(cdst + 1+2+4+4) = wc;
		*(word_t*)(cdst + len -1-2-4) = *(word_t*)(cdst + len -1-2-4-8) = wc;
		if (len <= 30) return dst;
		*(word_t*)(cdst + 1+2+4+8) = *(word_t*)(cdst + 1+2+4+8+4) = wc;
		*(word_t*)(cdst + 1+2+4+8+8) = *(word_t*)(cdst + 1+2+4+8+12) = wc;
		*(word_t*)(cdst + len -1-2-4-8-16) = *(word_t*)(cdst + len -1-2-4-8-12) = wc;
		*(word_t*)(cdst + len -1-2-4-8-8) = *(word_t*)(cdst + len -1-2-4-8-4) = wc;
	} else {
		*(word_t*)(cdst + len - 4) = wc;
		if ((uintptr_t)dst & 15) {
			word_t *wdst = dst;
			wdst[0] = wdst[1] = wdst[2] = wdst[3] = wc;
			cdst += (-(uintptr_t)dst) & 15;
		}
		len >>= 2;
		__asm__("rep; movsl" : "+c"(len), "+D"(cdst) :: "memory");
	}
	return dst;
}
