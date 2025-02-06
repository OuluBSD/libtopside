#ifndef _LittleCommon_Timer_h_
#define _LittleCommon_Timer_h_


struct Registers;


struct Timer {
	size_t tick = 0;
	size_t multiplier_tick = 0;
	size_t multiplier = 0;

	void Init(size_t frequency);
	void InterruptCallback(struct Registers regs);
};


#endif
