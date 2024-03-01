#include "Emu.h"


int syscall_MonitorWrite(const char* s) {
	ASSERT_USERMODE
	MON.Write(s);
	return 0;
}

int syscall_MonitorWriteHex(const char* s) {
	ASSERT_USERMODE
	MON.WriteHexPtr((void*)s);
	return 0;
}

int syscall_MonitorWriteDec(int s) {
	ASSERT_USERMODE
	MON.WriteDec(s);
	return 0;
}


void SyscallHandler(struct Registers regs);


void InitialiseSyscalls() {
	TRACE(InitialiseSyscalls)
	
	// Register our syscall handler.
	RegisterInterruptHandler(0x80, callback(&SyscallHandler));
}