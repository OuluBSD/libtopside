#include "EmuCtrl.h"


static void timer_callback(Registers regs)
{
    global->timer.InterruptCallback(regs);
}

void Timer::Init(size_t frequency) {
	tick = 0;
	multiplier_tick = 0;
	
    // Firstly, register our timer callback.
    RegisterInterruptHandler(IRQ0, callback(timer_callback));

    // Important to note is
    // that the divisor must be small enough to fit into 16-bits.
    uint32 divisor = frequency;
	multiplier = 1;
	while (divisor & 0xFFFF0000 || 1000 / divisor == 0) {
		multiplier <<= 1UL;
		divisor >>= 1UL;
	}
	
	int ms = max<int>(1, 1000 / divisor);
	static TimeCallback tc;
	tc.Set(-ms, []() {
		if (!GetThreadVars().disable_interrupts) // check enabled interrupts
			timer_callback(GetThreadVars().regs);
	});
}

void Timer::InterruptCallback(struct Registers regs) {
	if (++multiplier_tick >= multiplier) {
		tick++;
	    MON.Write("Tick: ");
	    MON.WriteDec(tick);
	    MON.Write("\n");
	    multiplier_tick = 0;
	}
}
