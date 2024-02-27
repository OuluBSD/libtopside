#ifndef _Emu_SysCall_h_
#define _Emu_SysCall_h_


EXTERN_C_BEGIN

struct Registers {
   size_t eax;
};

EXTERN_C_END


#define DEFN_SYSCALL1(fn, num, P1) \
	int syscall_##fn(P1 p1);

DEFN_SYSCALL1(MonitorWrite, 0, const char*);
DEFN_SYSCALL1(MonitorWriteHex, 1, void*);
DEFN_SYSCALL1(MonitorWriteDec, 2, int);


#endif
