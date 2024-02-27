#include "Emu.h"

void EnableInterrupts() {
	TRACE(EnableInterrupts)
	
}

void DisableInterrupts() {
	TRACE(DisableInterrupts)
	
}

void RegisterInterruptHandler(uint8 n, Callback1<Registers> handler) {
	global->interrupt_handlers[n] = handler;
	//interrupt_handlers[n].Copy(handler);
}
