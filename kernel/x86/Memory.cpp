#include "Kernel.h"

void operator delete(void*) {}
void operator delete(void*, unsigned int) {}
void* operator new(unsigned int) {return 0;}


// end is defined in the linker script.
extern size_t end;
extern size_t code;
extern size_t bss;
extern size_t data;
SVar* global = (SVar*)&end;

void InitLinkerVariables(size_t end) {
	if (end)
		global->placement_address = end + sizeof(SVar);
	else
		global->placement_address = (size_t)global + sizeof(SVar);
	KDUMPH(&code);
	KDUMPH(&data);
	KDUMPH(&bss);
	KDUMPH(&end);
}

