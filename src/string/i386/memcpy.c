#include <string.h>
#include <stdint.h>
#include "features.h"

void *memcpy(void *restrict dst, const void *restrict src, size_t len)
{
	void *odst = dst;
	/* little known fact about the rep prefix: if ECX==0, it turns into a NOP. */
	if (len >= 4) {
		size_t to_align = (-(uintptr_t)dst) & 3;
		len -= to_align;
		__asm__("rep; movsb" : "+c"(to_align), "+S"(src), "+D"(dst) :: "memory");
	}
	size_t words = len >> 2;
	__asm__("rep; movsl" : "+c"(words), "+S"(src), "+D"(dst) :: "memory");
	len &= 3;
	__asm__("rep; movsb" : "+c"(len), "+S"(src), "+D"(dst) :: "memory");
	return odst;
}

hidden void *__memcpy_fwd(void *restrict, const void *restrict, size_t) __attribute__((alias("memcpy")));
