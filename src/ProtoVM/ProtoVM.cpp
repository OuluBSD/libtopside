#include "ProtoVM.h"

void SetupUK101(Machine& mach);
void SetupInterak(Machine& mach);
void SetupMiniMax8085(Machine& mach);

CONSOLE_APP_MAIN {
	Machine		mach;
	int			max_ticks = 10;
	
	switch (0) {
		case 0: SetupUK101(mach); break;
		case 1: SetupInterak(mach); break;
		case 2: SetupMiniMax8085(mach); break;
		default: return;
	}
	
	if (mach.Init()) {
		
		for(int i = 0; i < max_ticks; i++) {
			
			mach.Tick();
			
		}
		
	}
}
