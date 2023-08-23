#ifndef _Emu_SysCall_h_
#define _Emu_SysCall_h_


#define DEFN_SYSCALL1(fn, num, P1) \
	int syscall_##fn(P1 p1);

DEFN_SYSCALL1(MonitorWrite, 0, const char*);
DEFN_SYSCALL1(MonitorWriteHex, 1, const char*);
DEFN_SYSCALL1(MonitorWriteDec, 2, const char*);


#endif
