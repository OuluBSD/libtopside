#include "Emu.h"

static InitrdHeader __initrd_header;

void FindRamDisk(struct multiboot *mboot_ptr, size_t& initrd_location) {
	// Find the location of our initial ramdisk.
	initrd_location = (size_t)&__initrd_header;
	
	InitLinkerVariables(0);
}

