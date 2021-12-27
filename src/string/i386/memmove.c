#include <string.h>
#include <stdint.h>
#include "features.h"

extern hidden void *__memcpy_fwd(void*, const void*, size_t); /* is this undefined behavior? */
void *memmove(void *dst, const void *src, size_t len)
{
	if ((uintptr_t)dst - (uintptr_t)src >= len)
		return __memcpy_fwd(dst, src, len);
	/* else we need to do the backward copy */
	dst = (char*)dst + len - 1;
	src = (const char*)src + len - 1;
	__asm__("std; rep; movsb; cld" : "+c"(len), "+D"(dst), "+S"(src) :: "memory");
	return (char*)dst + 1;
}
