#include "Kernel.h"


void operator delete(void*) {}
void operator delete(void*, unsigned int) {}
void* operator new(unsigned int) {return 0;}


// end is defined in the linker script.
extern uint32 end;
extern uint32 code;
extern uint32 bss;
extern uint32 data;
SVar* global = (SVar*)&end;

void InitLinkerVariables(uint32 end) {
	if (end)
		global->placement_address = end + sizeof(SVar);
	else
		global->placement_address = (uint32)global + sizeof(SVar);
	KDUMPH(&code);
	KDUMPH(&data);
	KDUMPH(&bss);
	KDUMPH(&end);
}

