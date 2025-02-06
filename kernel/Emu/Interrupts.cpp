#include "Emu.h"

void EnableInterrupts() {
	TRACE(EnableInterrupts)
	GetThreadVars().disable_interrupts = false;
}

void DisableInterrupts() {
	TRACE(DisableInterrupts)
	GetThreadVars().disable_interrupts = true;
}

void irq_handler(Registers regs) {
	
	TODO
	
}
