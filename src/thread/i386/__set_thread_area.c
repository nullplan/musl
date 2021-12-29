#define SYSCALL_NO_TLS 1  /* this file initializes the TLS, so it can't use it. */
#include "syscall.h"
#include <stdint.h>

int __set_thread_area(void *p)
{
	static int idx = -1;
	uint32_t buf[4] = {idx, (uint32_t)p, 0xfffff, 0x51};
	int rv = __syscall(SYS_set_thread_area, buf);
	int gsval;
	if (!rv) {
		idx = buf[0];
		gsval = 8 * buf[0] + 3;
	} else {
		rv = __syscall(SYS_modify_ldt, 1, buf, 16);
		if (!rv) {
			gsval = 7;
			rv = 1;
		}
	}
	if (rv >= 0)
		__asm__("movw %w0,%%gs" :: "r"(gsval) : "memory");
	return rv;
}
