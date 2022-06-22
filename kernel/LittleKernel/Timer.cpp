#include "Kernel.h"


static void timer_callback(Registers regs)
{
    global->timer.InterruptCallback(regs);
}

void Timer::Init(uint32 frequency)
{
	tick = 0;
	multiplier_tick = 0;
	
    // Firstly, register our timer callback.
    //RegisterInterruptHandler(IRQ0, &timer_callback);
    //RegisterInterruptHandler(IRQ0, Callback1<Registers>(timer_callback) );
    //Callback1<Registers> cb(timer_callback);
    //RegisterInterruptHandler(IRQ0, cb);
    RegisterInterruptHandler(IRQ0, timer_callback);

    // The value we send to the PIT is the value to divide it's input clock
    // (1193180 Hz) by, to get our required frequency. Important to note is
    // that the divisor must be small enough to fit into 16-bits.
    uint32 divisor = 1193180 / frequency;
	multiplier = 1;
	while (divisor & 0xFFFF0000) {
		multiplier <<= 1UL;
		divisor >>= 1UL;
	}
	
    // Send the command byte.
    outb(0x43, 0x36);

    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    uint8 l = (uint8)(divisor & 0xFF);
    uint8 h = (uint8)( (divisor>>8) & 0xFF );

    // Send the frequency divisor.
    outb(0x40, l);
    outb(0x40, h);
}

void Timer::InterruptCallback(Registers regs) {
	if (++multiplier_tick >= multiplier) {
		tick++;
	    MON.Write("Tick: ");
	    MON.WriteDec(tick);
	    MON.Write("\n");
	    multiplier_tick = 0;
	}
}
