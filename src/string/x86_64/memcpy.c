#include <string.h>
#include <stdint.h>
#include "features.h"

void *memcpy(void *restrict dst, const void *restrict src, size_t len)
{
	void *odst = dst;
	if (len >= 8) {
		while ((uintptr_t)dst & 7) {
			__asm__("movsb" : "+D"(dst), "+S"(src), "=m"(*(char*)dst) : "m"(*(char*)src));
			len--;
		}
	}
	size_t words = len >> 3;
	__asm__("rep; movsq" : "+c"(words), "+D"(dst), "+S"(src), "=m"(*(uint64_t(*)[words])dst) : "m"(*(uint64_t(*)[words])src));
	len &= 7;
	while (len--)
		__asm__("movsb" : "+D"(dst), "+S"(src), "=m"(*(char*)dst) : "m"(*(char*)src));
	return odst;
}

hidden void *__memcpy_fwd(void*, const void*, size_t) __attribute__((alias("memcpy")));
