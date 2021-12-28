#include <string.h>
#include <stdint.h>
#include "features.h"

extern hidden void *__memcpy_fwd(void*, const void*, size_t);

void *memmove(void *dst, const void *src, size_t len)
{
	if ((uintptr_t)dst - (uintptr_t)src >= len)
		return __memcpy_fwd(dst, src, len);
	dst = (char*)dst + len - 1;
	src = (char*)src + len - 1;
	__asm__ volatile("std; rep; movsb; cld" : "+D"(dst), "+S"(src), "+c"(len) :: "memory");
	return (char*)dst + 1;
}
