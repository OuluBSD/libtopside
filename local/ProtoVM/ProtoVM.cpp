#include "ProtoVM.h"

void SetupUK101(Machine& mach);
void SetupInterak(Machine& mach);

CONSOLE_APP_MAIN {
	Machine		mach;
	int			max_ticks = 10;
	
	
	
	if (mach.Init()) {
		
		for(int i = 0; i < max_ticks; i++) {
			
			mach.Tick();
			
		}
		
	}
}
