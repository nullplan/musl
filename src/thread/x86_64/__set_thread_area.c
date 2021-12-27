#include "syscall.h"
#include "features.h"

hidden int __set_thread_area(void *p)
{
	return __syscall(SYS_arch_prctl, 0x1002, p);
}
