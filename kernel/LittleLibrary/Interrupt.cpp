#include "LittleLibrary.h"


void RegisterInterruptHandler(uint8 n, Callback1<Registers> handler) {
	Callback1<Registers>& cb = global->interrupt_handlers[n];
	cb = handler;
	//bool& cb_enabled = global->interrupt_handlers_enabled[n];
	//cb_enabled = true;
	//interrupt_handlers[n].Copy(handler);
}

void ResetInterruptHandlers() {
	for (int i = 0; i < global->interrupt_handlers.GetCount(); i++)
		global->interrupt_handlers[i].Clear();
	//memset(&global->interrupt_handlers_enabled, 0, sizeof(global->interrupt_handlers_enabled));
}


// This gets called from our ASM interrupt handler stub.
void isr_handler(Registers regs) {
	/*MON.Write("recieved interrupt: ");
	MON.WriteDec(regs.int_no);
	MON.Write(" (").WriteDec(regs.err_code).Write(")");
	MON.Put('\n');*/
	
	//if (regs.int_no == 6)
	//	PANIC("id 6 is stuck");
	
	Callback1<Registers>& cb = global->interrupt_handlers[regs.int_no];
	if (cb) {
		//isr_t handler = interrupt_handlers[regs.int_no];
		//handler(regs);
		//MON.WriteDec(regs.int_no); MON.Write(" interrupted\n");
		
		global->interrupt_handlers[regs.int_no](regs);
	}
}


