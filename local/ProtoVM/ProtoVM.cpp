#include "ProtoVM.h"


CONSOLE_APP_MAIN {
	if (1) {
		TransArrayProc tap;
		int max_ticks = 10;
		
		tap.InitTest(0);
		
		for(int i = 0; i < max_ticks; i++) {
			
			tap.Tick();
			
		}
		
		
		
	}
	else {
		Machine		mach;
		int			max_ticks = 10;
		
		mach.Init();
		
		for(int i = 0; i < max_ticks; i++) {
			
			mach.Tick();
			
		}
	}
}
