#include "Emu.h"

void InitLinkerVariables(size_t end) {
	TRACE(InitLinkerVariables)
	
	if (end)
		global->placement_address = end + sizeof(SVar);
	else
		global->placement_address = (size_t)global + sizeof(SVar);
	/*KDUMPH(&code);
	KDUMPH(&data);
	KDUMPH(&bss);
	KDUMPH(&end);*/
}
