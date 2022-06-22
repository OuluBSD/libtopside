#ifndef _LittleKernel_Timer_h_
#define _LittleKernel_Timer_h_


#include "Common.h"

void init_timer(uint32 frequency);

struct Timer {
	uint32 tick = 0;
	uint32 multiplier_tick = 0;
	uint32 multiplier = 0;

	void Init(uint32 frequency);
	void InterruptCallback(Registers regs);
};


#endif
