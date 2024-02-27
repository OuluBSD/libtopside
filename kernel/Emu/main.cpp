#include "Emu.h"

void SetupEmu() {
	static Vector<byte> fixed_mem;
	fixed_mem.SetCount(1024 * 1024 * 64, 0);
	
	global = (SVar*)fixed_mem.Begin();
	
}

#if !EMUGUI

CONSOLE_APP_MAIN {
	
	int ret = multiboot_main(0);
	
}

#endif
