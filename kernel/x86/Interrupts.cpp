#include "Kernel.h"


//
// isr.c -- High level interrupt service routines and interrupt request handlers.
//          Part of this code is modified from Bran's kernel development tutorials.
//          Rewritten for JamesM's kernel development tutorials.
//


//isr_t interrupt_handlers[256];

/*void RegisterInterruptHandler(uint8 n, isr_t handler)
{
    interrupt_handlers[n] = handler;
}*/




void RegisterInterruptHandler(uint8 n, Callback1<Registers> handler) {
	global->interrupt_handlers[n] = handler;
	//interrupt_handlers[n].Copy(handler);
}

void ResetInterruptHandlers() {
	for (int i = 0; i < global->interrupt_handlers.GetCount(); i++)
		global->interrupt_handlers[i].Reset();
}


// This gets called from our ASM interrupt handler stub.
void isr_handler(Registers regs) {
	MON.Write("recieved interrupt: ");
	MON.WriteDec(regs.int_no);
	MON.Write(" (").WriteDec(regs.err_code).Write(")");
	MON.Put('\n');
	
	//if (regs.int_no == 6)
	//	PANIC("id 6 is stuck");
		
	if (global->interrupt_handlers[regs.int_no].IsNull() == false) {
		//isr_t handler = interrupt_handlers[regs.int_no];
		//handler(regs);
		//MON.WriteDec(regs.int_no); MON.Write(" interrupted\n");
		
		global->interrupt_handlers[regs.int_no].Execute(regs);
	}
}

// This gets called from our ASM interrupt handler stub.
void irq_handler(Registers regs) {
	if (regs.int_no != 32)
		MON.Write("irq_handler: int_no=").WriteDec(regs.int_no).Write(", err_code=").WriteDec(regs.err_code).NewLine();
	
	// Send an EOI (end of interrupt) signal to the PICs.
	// If this interrupt involved the slave.
	if (regs.int_no >= 40) {
		// Send reset signal to slave.
		outb(0xA0, 0x20);
	}
	// Send reset signal to master. (As well as slave, if necessary).
	outb(0x20, 0x20);
	
	//if (interrupt_handlers[regs.int_no] != 0) {
	if (global->interrupt_handlers[regs.int_no].IsNull() == false) {
		//isr_t handler = interrupt_handlers[regs.int_no];
		//handler(regs);
		//MON.WriteDec(regs.int_no); MON.Write(" interrupted\n");
		
		global->interrupt_handlers[regs.int_no].Execute(regs);
	}
	
}


void EnableInterrupts() {
	asm volatile("sti");
}

void DisableInterrupts() {
	asm volatile("cli");
}
