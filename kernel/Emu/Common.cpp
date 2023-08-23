#include "Emu.h"



void PanicAssert(const char *file, unsigned int line, const char *desc) {
	LOG("ASSERTION-FAILED(" << desc << ") at " << file << ":" << line);
	Panic("assertion failed");
}


void MagicBreakpoint() {
	__BREAK__;
}

void ResetInterruptHandlers() {}
