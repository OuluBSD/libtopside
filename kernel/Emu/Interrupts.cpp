#include "Emu.h"

void EnableInterrupts() {
	TRACE(EnableInterrupts)
	GetThreadVars().disable_interrupts = false;
}

void DisableInterrupts() {
	TRACE(DisableInterrupts)
	GetThreadVars().disable_interrupts = true;
}

void RegisterInterruptHandler(uint8 n, Callback1<Registers> handler) {
	global->interrupt_handlers[n] = handler;
	//interrupt_handlers[n].Copy(handler);
}
