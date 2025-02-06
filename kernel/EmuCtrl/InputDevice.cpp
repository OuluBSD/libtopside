#include "EmuCtrl.h"


extern int __emu_kb_char_queue[KB_QUEUE_LENGTH];

static void input_device_callback(Registers regs)
{
    global->input.InterruptCallback(regs);
}

void InputDevice::Init() {
	RegisterInterruptHandler(IRQ1, callback(input_device_callback));
	
}

void InputDevice::InterruptCallback(struct Registers regs) {
	// Read input device value
	if (input_fn) {
		for(int i = 0; i < KB_QUEUE_LENGTH; i++) {
			int& e = __emu_kb_char_queue[i];
			if (!e)
				continue;
			if (input_fn(e, 1, input_arg)) {
				e = 0;
			}
			else break;
		}
	}
}
