#include "Emu.h"

void InitialiseTasking() {
	TRACE(InitialiseTasking)
	
}

void SwitchToUserMode() {
	TRACE(SwitchToUserMode)
	GetThreadVars().user_mode = true;
}

void SyscallHandler(struct Registers regs) {
	// Firstly, check if the requested syscall number is valid.
	// The syscall number is found in EAX.
	if (regs.eax >= global->num_syscalls)
		return;
		
	// Get the required syscall location.
	void *location = global->syscalls[regs.eax];
	
	TODO
}
