#include "Kernel.h"


static void SyscallHandler(Registers regs);

DEFN_SYSCALL1(MonitorWrite, 0, const char*);
DEFN_SYSCALL1(MonitorWriteHex, 1, const char*);
DEFN_SYSCALL1(MonitorWriteDec, 2, const char*);


void InitialiseSyscalls() {
	// Register our syscall handler.
	RegisterInterruptHandler(0x80, &SyscallHandler);
}

void SyscallHandler(Registers regs) {
	// Firstly, check if the requested syscall number is valid.
	// The syscall number is found in EAX.
	if (regs.eax >= global->num_syscalls)
		return;
		
	// Get the required syscall location.
	void *location = global->syscalls[regs.eax];
	
	// We don't know how many parameters the function wants, so we just
	// push them all onto the stack in the correct order. The function will
	// use all the parameters it wants, and we can pop them all back off afterwards.
	int ret;
	asm volatile(" \
				 push %1; \
				 push %2; \
				 push %3; \
				 push %4; \
				 push %5; \
				 call *%6; \
				 pop %%ebx; \
				 pop %%ebx; \
				 pop %%ebx; \
				 pop %%ebx; \
				 pop %%ebx; \
			 " : "=a" (ret) : "r" (regs.edi), "r" (regs.esi), "r" (regs.edx), "r" (regs.ecx), "r" (regs.ebx), "r" (location));
	regs.eax = ret;
}
