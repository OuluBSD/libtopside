#include "Emu.h"

Vector<byte>& FixedMem() {
	static Vector<byte> fixed_mem;
	return fixed_mem;
}

void SetupEmu() {
	auto& fixed_mem = FixedMem();
	fixed_mem.SetCount(1024 * 1024 * 65, 0);
	
	global = (SVar*)(fixed_mem.Begin() + 0x1000);
	
}

void CloseEmu() {
	auto& fixed_mem = FixedMem();
	fixed_mem.Clear();
}

#if !EMUGUI

CONSOLE_APP_MAIN {
	
	int ret = multiboot_main(0);
	
}

#endif
