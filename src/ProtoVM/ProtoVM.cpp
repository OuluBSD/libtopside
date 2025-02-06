#include "ProtoVM.h"

/*
Links:
	- https://github.com/vygr/C-PCB
	- https://github.com/robfinch/Cores/tree/master/bc6502
	- http://www.aholme.co.uk/6502/Main.htm
*/


NAMESPACE_TOPSIDE_BEGIN

void SetupTest1_Memory(Machine& mach);
void SetupTest2_6502(Machine& mach);
void SetupUK101(Machine& mach);
void SetupInterak(Machine& mach);
void SetupMiniMax8085(Machine& mach);

NAMESPACE_TOPSIDE_END

#ifdef flagMAIN

CONSOLE_APP_MAIN {
	using namespace TS;
	
	Machine		mach;
	int			max_ticks = 100;
	
	switch (1) {
		case 0: SetupTest1_Memory(mach); break;
		case 1: SetupTest2_6502(mach); break;
		/*case 0: SetupUK101(mach); break;
		case 1: SetupInterak(mach); break;
		case 2: SetupMiniMax8085(mach); break;*/
		default: return;
	}
	
	
	if (1) {
		for (Pcb& pcb : mach.pcbs) {
			LOG(pcb.ToVerilog());
		}
	}
	else {
		if (mach.Init()) {
			
			for(int i = 0; i < max_ticks; i++) {
				LOG("Tick " << i);
				
				if (!mach.Tick())
					break;
				
			}
			
		}
	}
}

#endif
