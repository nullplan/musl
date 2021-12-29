#include <string.h>
#include <stdint.h>

void *memset(void *dst, int c, size_t len)
{
	uint64_t wc = 0x0101010101010101 * (c & 0xff);
	char *cdst = dst;
	typedef uint16_t __attribute__((may_alias)) quarterword_t;
	typedef uint32_t __attribute__((may_alias)) halfword_t;
	typedef uint64_t __attribute__((may_alias)) word_t;
	if (len <= 126) {
		if (!len) return dst;
		cdst[0] = cdst[len - 1] = c;
		if (len <= 2) return dst;
		*(quarterword_t*)(cdst+1) = *(quarterword_t*)(cdst+len-1-2) = wc;
		if (len <= 6) return dst;

		*(halfword_t*)(cdst+1+2) = *(halfword_t*)(cdst+len-1-2-4) = wc;
		if (len <= 14) return dst;

		*(word_t*)(cdst+1+2+4) = *(word_t*)(cdst+len-1-2-4-8) = wc;
		if (len <= 30) return dst;

		*(word_t*)(cdst+1+2+4+8) = *(word_t*)(cdst+1+2+4+8+8) = wc;
		*(word_t*)(cdst+len-1-2-4-8-16) = *(word_t*)(cdst+len-1-2-4-8-8) = wc;
		if (len <= 62) return dst;

		*(word_t*)(cdst+1+2+4+8+16) = *(word_t*)(cdst+1+2+4+8+16+8) = wc;
		*(word_t*)(cdst+1+2+4+8+16+16) = *(word_t*)(cdst+1+2+4+8+24) = wc;
		*(word_t*)(cdst+len-1-2-4-8-16-32) = *(word_t*)(cdst+len-1-2-4-8-16-24) = wc;
		*(word_t*)(cdst+len-1-2-4-8-16-16) = *(word_t*)(cdst+len-1-2-4-8-16-8) = wc;
	} else {
		*(word_t*)(cdst+len-8) = wc;
		if ((uintptr_t)cdst & 15) {
			*(word_t*)cdst = *(word_t*)(cdst + 8) = wc;
			cdst += (-(uintptr_t)cdst) & 15;
		}
		size_t words = len >> 3;
		__asm__ volatile ("rep; stosq" : "+c"(words), "+D"(cdst) : "a"(wc) : "memory");
	}
	return dst;
}
