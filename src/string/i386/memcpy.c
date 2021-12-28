#include <string.h>
#include <stdint.h>
#include "features.h"

void *memcpy(void *restrict dst, const void *restrict src, size_t len)
{
	void *odst = dst;
	if (len >= 4)
		while ((uintptr_t)dst & 3) {
			len--;
			__asm__("movsb" : "=m"(*(char*)dst), "+S"(src), "+D"(dst) : "m"(*(char*)src));
		}

	size_t words = len >> 2;
	__asm__("rep; movsl" : "=m"(*(uint32_t(*)[words])dst), "+c"(words), "+S"(src), "+D"(dst) : "m"(*(uint32_t(*)[words])src));
	len &= 3;
	while (len--)
		__asm__("movsb" : "=m"(*(char*)dst), "+S"(src), "+D"(dst) : "m"(*(char*)src));
	return odst;
}

hidden void *__memcpy_fwd(void *restrict, const void *restrict, size_t) __attribute__((alias("memcpy")));
